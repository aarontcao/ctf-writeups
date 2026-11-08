<?php




require_once __DIR__ . '/../lib/util.php';
require_once __DIR__ . '/../lib/archive.php';

function vk_verify_bundle(string $raw): array {
    $entries = vk_tar_parse($raw);
    $report  = [];
    $manifest = 0; $absolute = 0; $links = 0;
    foreach ($entries as $e) {
        $name = (string) $e['name'];
        if (basename($name) === 'database.sql') $manifest++;
        if (strlen($name) && $name[0] === '/') $absolute++;
        if ($e['type'] === '2') $links++;
        $report[] = [
            'name'   => $name,
            'type'   => $e['type'] === '5' ? 'dir' : ($e['type'] === '2' ? 'link' : 'file'),
            'bytes'  => strlen($e['data']),
            'sha256' => $e['data'] !== '' ? substr(hash('sha256', $e['data']), 0, 32) : null,
        ];
    }
    $issues = [];
    if ($manifest === 0) $issues[] = 'no database.sql manifest';
    if ($manifest > 1)   $issues[] = 'multiple database.sql manifests';
    if ($absolute > 0)   $issues[] = "$absolute entry(ies) use an absolute path";
    return [
        'entries'  => count($entries),
        'manifest' => $manifest,
        'symlinks' => $links,
        'sha256'   => hash('sha256', $raw),
        'well_formed' => empty($issues),
        'issues'   => $issues,
        'objects'  => array_slice($report, 0, 200),
    ];
}
