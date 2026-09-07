<?php

require_once __DIR__ . '/../../lib/db.php';
require_once __DIR__ . '/../../lib/util.php';

$rows = db()->query(
    "SELECT id, kind, source_label, status, created_at, updated_at
     FROM jobs ORDER BY id DESC LIMIT 50"
)->fetchAll();

$out = [];
foreach ($rows as $r) {
    $out[] = [
        'id'        => (int) $r['id'],
        'kind'      => $r['kind'],
        'source'    => $r['source_label'],
        'status'    => $r['status'],
        
        'queued_at' => gmdate('c', (int) $r['created_at']),
        'updated'   => sprintf('%.3f', (float) $r['updated_at']),
    ];
}
vk_json(['appliance' => 'vaultkeeper', 'queue' => $out]);
