<?php



require_once __DIR__ . '/util.php';
require_once __DIR__ . '/store.php';
require_once __DIR__ . '/request.php';

function vk_tags_all(): array {
    return vk_store_load('tags', [
        ['snapshot' => 1, 'key' => 'tier',   'value' => 'gold'],
        ['snapshot' => 1, 'key' => 'team',   'value' => 'platform'],
        ['snapshot' => 3, 'key' => 'hold',   'value' => 'legal'],
    ]);
}

function vk_tags_for(int $snapshot): array {
    return array_values(array_filter(vk_tags_all(), fn($t) => (int) ($t['snapshot'] ?? -1) === $snapshot));
}

function vk_tag_add(int $snapshot, string $key, string $value): array {
    $rows = vk_store_load('tags', []);
    if (!$rows) { $rows = vk_tags_all(); }
    $key   = substr(preg_replace('/[^a-z0-9_.-]/i', '', $key), 0, 32);
    $value = substr($value, 0, 64);
    $rows[] = ['snapshot' => $snapshot, 'key' => $key, 'value' => $value];
    vk_store_save('tags', $rows);
    return ['snapshot' => $snapshot, 'key' => $key, 'value' => $value];
}


function vk_tag_keys(): array {
    $keys = [];
    foreach (vk_tags_all() as $t) $keys[$t['key'] ?? ''] = true;
    unset($keys['']);
    return array_keys($keys);
}
