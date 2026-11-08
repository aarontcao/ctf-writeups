<?php



require_once __DIR__ . '/util.php';
require_once __DIR__ . '/db.php';
require_once __DIR__ . '/store.php';
require_once __DIR__ . '/ids.php';
require_once __DIR__ . '/request.php';

function vk_saved_searches(): array {
    return vk_store_load('searches', [
        ['id' => 'srch_big',    'name' => 'Large backups', 'filter' => "kind = 'backup' AND bytes > 1000000000"],
        ['id' => 'srch_restore','name' => 'Restore points','filter' => "kind = 'restore'"],
    ]);
}

function vk_saved_search_save(array $in): array {
    $rec = vk_pick($in, ['id' => 'str', 'name' => 'str', 'filter' => 'text']);
    if (!vk_store_load('searches', [])) vk_store_save('searches', vk_saved_searches());
    $rec['id'] = $rec['id'] ?? ('srch_' . vk_short_ref($rec['name'] ?? ''));
    return vk_store_upsert('searches', $rec);
}


function vk_run_catalog_search(string $filter, int $limit = 50): array {
    $filter = trim($filter);
    if ($filter === '') $filter = '1=1';
    $sql = "SELECT id, name, bytes, kind FROM catalog WHERE $filter ORDER BY id LIMIT $limit";
    try {
        $rows = db_restore()->query($sql)->fetchAll();
        return ['ok' => true, 'count' => count($rows), 'results' => $rows];
    } catch (Throwable $e) {
        return ['ok' => false, 'error' => $e->getMessage(), 'results' => []];
    }
}
