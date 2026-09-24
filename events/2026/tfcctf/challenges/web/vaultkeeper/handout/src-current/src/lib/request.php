<?php

require_once __DIR__ . '/util.php';

function vk_method(): string { return $_SERVER['REQUEST_METHOD'] ?? 'GET'; }


function vk_input(): array {
    $raw = file_get_contents('php://input');
    if ($raw !== '' && $raw !== false) {
        $j = json_decode($raw, true);
        if (is_array($j)) return $j;
    }
    return is_array($_POST) ? $_POST : [];
}


function vk_pick(array $src, array $spec): array {
    $out = [];
    foreach ($spec as $k => $type) {
        if (!array_key_exists($k, $src)) continue;
        $v = $src[$k];
        switch ($type) {
            case 'int':  $out[$k] = (int) $v; break;
            case 'bool': $out[$k] = (bool) $v; break;
            case 'str':  $out[$k] = substr((string) $v, 0, 256); break;
            case 'text': $out[$k] = substr((string) $v, 0, 4096); break;
            case 'list': $out[$k] = is_array($v) ? array_slice(array_map('strval', $v), 0, 64) : []; break;
            default:     $out[$k] = is_scalar($v) ? (string) $v : '';
        }
    }
    return $out;
}

function vk_slug(string $s): string {
    $s = strtolower(preg_replace('/[^A-Za-z0-9]+/', '-', $s));
    return trim($s, '-') ?: 'item';
}
