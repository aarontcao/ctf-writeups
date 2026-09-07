<?php
/*
 * Local MOCK of the DEPLOYED vaultkeeper renderer: the `[[ path|filter:arg ]]`
 * filter engine. The handout ships the old `{{ }}` expression engine, so this
 * file exists purely as an instrument to validate solve/probe_taint.py offline
 * before any request is spent on the shared live instance.
 *
 * It reproduces every behaviour the live target is recorded to have:
 *   [[node|at:1]]        -> 'o'
 *   [[node|slice:1:2]]   -> 'od'
 *   [[node|len]]         -> '6'
 *   [[node|add:5]]       -> '5'
 *   [[node|char]]        -> chr(0)
 *   [[node|upper|lower]] -> 'node-a'
 *   unknown filter       -> the whole [[...]] echoed back
 *   any error            -> ''
 *   tainted subject      -> '[redacted]' through every filter
 *
 * VK_MOCK_MODE picks the variant under test:
 *   A  mul is UNCAST  ($v * $arg): a non-numeric string throws TypeError.
 *   B  mul is CAST    ((int)$v * $arg): nothing can throw. Negative control.
 *   C  taint is checked at resolve time, before the filters run. Negative control.
 */
require_once __DIR__ . '/../../lib/util.php';
require_once __DIR__ . '/../../lib/request.php';

if (vk_method() !== 'POST') vk_json(['error' => 'POST only'], 405);

$body     = vk_input();
$template = substr((string) ($body['template'] ?? ''), 0, 2000);
$event    = (string) ($body['event'] ?? 'restore.failed');
$MODE     = getenv('VK_MOCK_MODE') ?: 'A';

$mask = is_readable('/var/www/private/cap.mask')
      ? trim((string) @file_get_contents('/var/www/private/cap.mask')) : '';

$ctx = [
    'event' => $event, 'appliance' => 'vaultkeeper',
    'node' => getenv('VK_NODE') ?: 'node-a', 'job' => '#1042',
    'source' => 'nightly / full', 'status' => 'failed',
    'when' => gmdate('c'), 'workspace' => 'Acme Platform',
];
if (preg_match('/^maintenance\./', $event)) {
    $ctx['config'] = [
        'retention_days' => (int) (getenv('VK_RETENTION') ?: 30),
        'cluster_node'   => getenv('VK_NODE') ?: 'node-a',
        'cap_mask'       => $mask,
        'version'        => '4.2.1',
    ];
}

function vk_hint_int(int $n): int { return $n; }

final class VkVal { public function __construct(public mixed $v, public bool $t = false) {} }

final class VkPipe {
    private array $f;
    public function __construct(private array $ctx, private array $secrets, private string $mode) {
        $uncast = fn($v, $a) => $v * (int) ($a[0] ?? 1);
        $cast   = fn($v, $a) => (int) $v * (int) ($a[0] ?? 1);
        $this->f = [
            'upper' => fn($v, $a) => strtoupper((string) $v),
            'lower' => fn($v, $a) => strtolower((string) $v),
            'len'   => fn($v, $a) => strlen((string) $v),
            'trim'  => fn($v, $a) => trim((string) $v),
            'slice' => fn($v, $a) => substr((string) $v, (int) ($a[0] ?? 0),
                                            isset($a[1]) ? (int) $a[1] : null),
            'sub'   => fn($v, $a) => (int) $v - (int) ($a[0] ?? 0),
            'at'    => fn($v, $a) => (string) @((string) $v)[(int) ($a[0] ?? 0)],
            'char'  => $mode === 'D' ? fn($v, $a) => chr(vk_hint_int($v))
                                     : fn($v, $a) => chr((int) $v),
            'mul'   => $mode === 'A' ? $uncast : $cast,   // D keeps mul cast on purpose
            'add'   => fn($v, $a) => (int) $v + (int) ($a[0] ?? 0),
            'code'  => fn($v, $a) => ord((string) $v),
        ];
    }
    public function render(string $tpl): string {
        return (string) preg_replace_callback('/\[\[(.*?)\]\]/s', function ($m) {
            try {
                $parts = explode('|', trim($m[1]));
                $val   = $this->subject(trim((string) array_shift($parts)));
                if ($this->mode === 'C' && $val->t) return '[redacted]';
                foreach ($parts as $p) {
                    $bits = explode(':', $p);
                    $name = trim((string) array_shift($bits));
                    if (!isset($this->f[$name])) return $m[0];
                    $val = new VkVal(($this->f[$name])($val->v, $bits), $val->t);
                }
                if ($val->t) return '[redacted]';
                return is_scalar($val->v) ? (string) $val->v : json_encode($val->v);
            } catch (\Throwable $e) {
                return '';
            }
        }, $tpl);
    }
    private function subject(string $s): VkVal {
        if (strlen($s) >= 2 && $s[0] === "'" && substr($s, -1) === "'")
            return new VkVal(substr($s, 1, -1), false);
        $v = $this->ctx;
        foreach (explode('.', $s) as $p) {
            if (is_array($v) && array_key_exists($p, $v)) $v = $v[$p];
            else return new VkVal('', false);
        }
        if (!is_scalar($v)) {
            $j = (string) json_encode($v);
            foreach ($this->secrets as $sec)
                if ($sec !== '' && strpos($j, (string) $sec) !== false) return new VkVal($j, true);
            return new VkVal($j, false);
        }
        return new VkVal($v, in_array((string) $v, $this->secrets, true));
    }
}

$secrets = array_values(array_filter([$mask], 'strlen'));
try {
    $rendered = (new VkPipe($ctx, $secrets, $MODE))->render($template);
    foreach ($secrets as $s) if ($s !== '') $rendered = str_replace((string) $s, '[redacted]', (string) $rendered);
} catch (\Throwable $e) {
    vk_json(['event' => $event, 'ok' => false, 'error' => 'render error'], 500);
}
vk_json(['event' => $event, 'ok' => true, 'rendered' => $rendered, 'tokens' => array_keys($ctx)]);
