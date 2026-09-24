<?php

require_once __DIR__ . '/../lib/db.php';
require_once __DIR__ . '/../lib/util.php';


function vk_replicate_manifest(): array {
    $rows = db_restore()->query(
        "SELECT table_name FROM information_schema.tables
         WHERE table_schema = 'vk_restore' AND table_type = 'BASE TABLE'"
    )->fetchAll(PDO::FETCH_COLUMN);

    $out = [];
    foreach ($rows as $name) {
        $q = '`' . str_replace('`', '``', (string) $name) . '`';   
        try {
            $n = (int) db_restore()->query("SELECT COUNT(*) FROM `vk_restore`.$q")->fetchColumn();
        } catch (Throwable $e) {
            $n = -1;
        }
        $out[$name] = $n;
    }
    return $out;
}
