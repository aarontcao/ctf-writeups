<?php

function vk_log(string $event, array $ctx = []): void {
    $line = json_encode(['ts' => microtime(true), 'event' => $event, 'ctx' => $ctx], JSON_UNESCAPED_SLASHES);
    @file_put_contents('/var/www/data/audit.log', $line . "\n", FILE_APPEND);
}

function vk_audit_tail(int $n = 50): array {
    $p = '/var/www/data/audit.log';
    if (!is_file($p)) return [];
    $lines = @file($p, FILE_IGNORE_NEW_LINES) ?: [];
    return array_slice($lines, -$n);
}
