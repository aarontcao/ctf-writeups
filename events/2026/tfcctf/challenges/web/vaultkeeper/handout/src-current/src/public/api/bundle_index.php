<?php




require_once __DIR__ . '/../../lib/db.php';
require_once __DIR__ . '/../../lib/util.php';

$kind = $_GET['kind'] ?? '';
$sort = (string) ($_GET['sort'] ?? 'id');
$dir  = strtoupper((string) ($_GET['dir'] ?? 'asc')) === 'DESC' ? 'DESC' : 'ASC';
$allowed_sort = ['id', 'name', 'bytes', 'kind'];
if (!in_array($sort, $allowed_sort, true)) $sort = 'id';

$rows = [];
try {
    if ($kind !== '') {
        $st = db_restore()->prepare("SELECT id, name, bytes, kind FROM catalog WHERE kind = ? ORDER BY $sort $dir LIMIT 50");
        $st->execute([$kind]);
    } else {
        $st = db_restore()->prepare("SELECT id, name, bytes, kind FROM catalog ORDER BY $sort $dir LIMIT 50");
        $st->execute([]);
    }
    $rows = $st->fetchAll();
} catch (Throwable $e) {
    vk_json(['sort' => $sort, 'error' => $e->getMessage(), 'results' => []]);
}

vk_json(['sort' => $sort, 'dir' => $dir, 'count' => count($rows), 'results' => $rows]);
