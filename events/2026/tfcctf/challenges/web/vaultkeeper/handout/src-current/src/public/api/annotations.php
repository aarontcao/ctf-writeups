<?php



require_once __DIR__ . '/../../lib/util.php';
require_once __DIR__ . '/../../lib/store.php';
require_once __DIR__ . '/../../lib/ids.php';
require_once __DIR__ . '/../../lib/request.php';

if (vk_method() === 'POST') {
    $body   = vk_input();
    $ref    = preg_replace('/[^a-f0-9]/', '', strtolower((string) ($body['ref'] ?? '')));
    $author = substr((string) ($body['author'] ?? 'operator'), 0, 64);
    $note   = substr((string) ($body['note'] ?? ''), 0, 1000);
    if ($ref === '' || $note === '') vk_json(['error' => 'ref and note required'], 400);
    $rec = [
        'id'     => vk_short_ref($ref . $note),
        'ref'    => $ref,
        'author' => $author,
        'note'   => $note,
        'ts'     => gmdate('c'),
    ];
    vk_store_upsert('annotations', $rec);
    vk_json(['ok' => true, 'id' => $rec['id']]);
}

$ref  = preg_replace('/[^a-f0-9]/', '', strtolower((string) ($_GET['ref'] ?? '')));
$rows = array_values(array_filter(vk_store_load('annotations', []), fn($r) => ($r['ref'] ?? '') === $ref));
vk_json(['ref' => $ref, 'count' => count($rows), 'annotations' => $rows]);
