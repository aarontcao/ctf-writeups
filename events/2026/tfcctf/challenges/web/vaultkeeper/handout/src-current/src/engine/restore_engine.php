<?php

require_once __DIR__ . '/../lib/db.php';
require_once __DIR__ . '/../lib/util.php';
require_once __DIR__ . '/../lib/archive.php';


function vk_staging_table_set(): array {
    $rows = db_restore()->query(
        "SELECT table_name FROM information_schema.tables
         WHERE table_schema = 'vk_restore' AND table_type = 'BASE TABLE'"
    )->fetchAll(PDO::FETCH_COLUMN);
    return array_map('strval', $rows);
}


function vk_import_database(string $sql): array {
    
    db()->query("SELECT GET_LOCK('vk_import', 10)")->fetchColumn();
    try {
        $before = vk_staging_table_set();
        db_restore()->exec($sql);
        $after   = vk_staging_table_set();
        $created = array_values(array_diff($after, $before));

        $dropped = [];
        foreach ($created as $name) {
            db()->exec("DROP TABLE IF EXISTS `vk_restore`.`$name`");
            $dropped[] = $name;
        }
        return ['created' => $created, 'dropped' => $dropped];
    } finally {
        db()->query("SELECT RELEASE_LOCK('vk_import')")->fetchColumn();
    }
}


function vk_restore_files(array $entries, int $job_id): array {
    $dest = VK_DATA . '/restore_' . $job_id;
    @mkdir($dest, 0755, true);
    return vk_tar_extract($entries, $dest);
}
