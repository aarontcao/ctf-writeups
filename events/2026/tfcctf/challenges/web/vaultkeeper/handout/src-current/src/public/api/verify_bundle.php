<?php



require_once __DIR__ . '/../../lib/util.php';
require_once __DIR__ . '/../../lib/archive.php';
require_once __DIR__ . '/../../lib/plugins.php';   

if ($_SERVER['REQUEST_METHOD'] !== 'POST' || empty($_FILES['bundle']['tmp_name'])) {
    vk_json(['error' => 'POST a bundle file'], 400);
}

$raw     = file_get_contents($_FILES['bundle']['tmp_name'], false, null, 0, 2 * 1024 * 1024);
$entries = vk_tar_parse((string) $raw);
$names   = array_map(fn($e) => $e['name'], $entries);

vk_json([
    'entries'      => count($entries),
    'names'        => array_slice($names, 0, 100),
    'has_manifest' => vk_tar_get($entries, 'database.sql') !== null,
    'note'         => 'inspection only; use the restore console to import',
]);
