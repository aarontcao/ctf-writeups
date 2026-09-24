<?php
/**
 * Notification renderer.
 *
 * Restore/backup notification bodies are authored as small templates. Any
 * "[[ ... ]]" span is a value pipeline: a seed (a context field, a quoted
 * literal, or "#<int>") passed left-to-right through a chain of "| filter"
 * stages. Rendered pipelines that resolve to protected appliance material are
 * masked; a stage that cannot be evaluated leaves its span untouched so the
 * operator can see which expression failed.
 */

require_once __DIR__ . '/../../lib/util.php';
require_once __DIR__ . '/../../lib/request.php';

if (vk_method() !== 'POST') vk_json(['error' => 'POST only'], 405);

$body     = vk_input();
$template = substr((string) ($body['template'] ?? ''), 0, 2000);
$event    = (string) ($body['event'] ?? 'restore.failed');

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

/** A pipeline value plus a "protected" flag that survives every stage. */
final class VkField {
    public function __construct(public mixed $v, public bool $protected = false) {}
}

final class VkPipeline {
    public function __construct(private array $ctx, private array $secrets) {}

    public function render(string $tpl): string {
        return preg_replace_callback('/\[\[(.*?)\]\]/s', function ($m) {
            try {
                $f = $this->chain($m[1]);
            } catch (\Throwable $e) {
                // Unevaluable span: surface it verbatim for the author to fix.
                return $m[0];
            }
            if ($f->protected) return '[redacted]';
            return is_scalar($f->v) ? (string) $f->v : (string) json_encode($f->v);
        }, $tpl);
    }

    private function chain(string $expr): VkField {
        $parts = explode('|', $expr);
        $cur   = $this->seed(trim((string) array_shift($parts)));
        foreach ($parts as $p) {
            $p = trim($p);
            if ($p === '') continue;
            $seg  = explode(':', $p);
            $name = trim((string) array_shift($seg));
            $cur  = $this->stage($name, $cur, array_map('trim', $seg));
        }
        return $cur;
    }

    private function seed(string $s): VkField {
        if ($s === '') return new VkField('', false);
        if (preg_match('/^#(-?\d+)$/', $s, $mm))   return new VkField((int) $mm[1], false);
        if (preg_match("/^'((?:[^'\\\\]|\\\\.)*)'$/s", $s, $mm)) return new VkField(stripcslashes($mm[1]), false);
        $v = $this->ctx;
        foreach (explode('.', $s) as $k) {
            if (is_array($v) && array_key_exists($k, $v)) $v = $v[$k];
            else return new VkField('', false);
        }
        if (!is_scalar($v)) {
            $j = (string) json_encode($v);
            return new VkField($j, $this->hits($j));
        }
        return new VkField($v, in_array((string) $v, $this->secrets, true));
    }

    private function hits(string $j): bool {
        foreach ($this->secrets as $s) { if ($s !== '' && strpos($j, (string) $s) !== false) return true; }
        return false;
    }

    // Filters carry the protected flag through unchanged; the value itself may
    // change type. Numeric stages coerce with (int).
    private function stage(string $name, VkField $in, array $a): VkField {
        $p = $in->protected;
        switch ($name) {
            case 'len':    return new VkField(strlen((string) $in->v), $p);
            case 'at':     return new VkField(substr((string) $in->v, (int) ($a[0] ?? 0), 1), $p);
            case 'slice':  return new VkField(substr((string) $in->v, (int) ($a[0] ?? 0), isset($a[1]) ? (int) $a[1] : null), $p);
            case 'code':   return new VkField(ord((string) $in->v), $p);
            case 'char':   return new VkField(chr(((int) $in->v) & 0xff), $p);
            case 'add':    return new VkField((int) $in->v + (int) ($a[0] ?? 0), $p);
            case 'sub':    return new VkField((int) $in->v - (int) ($a[0] ?? 0), $p);
            case 'mul':    return new VkField((int) $in->v * (int) ($a[1] ?? ($a[0] ?? 1)), $p);
            case 'upper':  return new VkField(strtoupper((string) $in->v), $p);
            case 'lower':  return new VkField(strtolower((string) $in->v), $p);
            case 'trim':   return new VkField(trim((string) $in->v), $p);
            // Fixed-width gauge/spacer used in status lines. Width is the piped
            // integer; the run character defaults to the block glyph.
            case 'bar':    return new VkField(str_repeat((string) ($a[0] ?? "\u{2588}"), (int) $in->v), $p);
            default:       throw new RuntimeException('unknown filter: ' . $name);
        }
    }
}

$secrets = array_values(array_filter([$mask], 'strlen'));
try {
    $rendered = (new VkPipeline($ctx, $secrets))->render($template);
    // Belt-and-braces: never let raw protected material survive in the body.
    foreach ($secrets as $s) { if ($s !== '') $rendered = str_replace((string) $s, '[redacted]', (string) $rendered); }
} catch (\Throwable $e) {
    vk_json(['event' => $event, 'ok' => false, 'error' => 'render error'], 500);
}
vk_json(['event' => $event, 'ok' => true, 'rendered' => $rendered, 'tokens' => array_keys($ctx)]);
