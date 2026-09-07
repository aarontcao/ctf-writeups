<?php



require_once __DIR__ . '/../../lib/request.php';
require_once __DIR__ . '/../../lib/archive.php';
require_once __DIR__ . '/../../lib/models.php';

if (vk_method() !== 'POST' || empty($_FILES['bundle']['tmp_name'])) {
    vk_json(['error' => 'POST a bundle as multipart field "bundle"'], 400);
}
$raw     = (string) @file_get_contents($_FILES['bundle']['tmp_name']);
$entries = vk_tar_parse($raw);
$files = 0; $dirs = 0; $links = 0; $bytes = 0; $names = [];
foreach ($entries as $e) {
    $t = $e['type'];
    if ($t === '5' || substr(trim($e['name']), -1) === '/') $dirs++;
    elseif ($t === '2') $links++;
    else { $files++; $bytes += strlen($e['data']); }
    if (count($names) < 200) $names[] = basename($e['name']);
}
$hasManifest = vk_tar_get($entries, 'database.sql') !== null;
vk_json([
    'bytes'        => strlen($raw),
    'entries'      => count($entries),
    'files'        => $files, 'dirs' => $dirs, 'symlinks' => $links,
    'payload'      => vk_human_bytes($bytes),
    'has_manifest' => $hasManifest,
    'sha256'       => hash('sha256', $raw),
    'names'        => $names,
]);
