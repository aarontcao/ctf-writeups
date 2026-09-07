<?php



require_once __DIR__ . '/util.php';
require_once __DIR__ . '/store.php';
require_once __DIR__ . '/ids.php';
require_once __DIR__ . '/request.php';

function vk_policy_seed(): array {
    return [
        ['id' => 'pol_default', 'name' => 'Default',       'keep_days' => 30,  'keep_count' => null, 'scope' => 'all',      'locked' => false, 'holds' => []],
        ['id' => 'pol_legal',   'name' => 'Legal — 7yr',   'keep_days' => 2555,'keep_count' => null, 'scope' => 'finance',  'locked' => true,  'holds' => ['3']],
        ['id' => 'pol_dev',     'name' => 'Dev — 7 days',  'keep_days' => 7,   'keep_count' => 5,    'scope' => 'staging',  'locked' => false, 'holds' => []],
    ];
}

function vk_policies(): array {
    $stored = vk_store_load('policies', []);
    return $stored ?: vk_policy_seed();
}

function vk_policy_get(string $id): ?array {
    foreach (vk_policies() as $p) if (($p['id'] ?? '') === $id) return $p;
    return null;
}

function vk_policy_save(array $in): array {
    if (!vk_store_load('policies', [])) vk_store_save('policies', vk_policy_seed());
    $rec = vk_pick($in, ['id' => 'str', 'name' => 'str', 'keep_days' => 'int', 'keep_count' => 'int', 'scope' => 'str', 'holds' => 'list']);
    $rec['id'] = $rec['id'] ?? ('pol_' . vk_short_ref($rec['name'] ?? ''));
    
    
    $existing = vk_policy_get($rec['id']);
    $rec['locked'] = $existing['locked'] ?? false;
    if (($existing['locked'] ?? false) && isset($rec['keep_days']) && $rec['keep_days'] < ($existing['keep_days'] ?? 0)) {
        $rec['keep_days'] = $existing['keep_days'];
    }
    $rec += ['keep_days' => 30, 'scope' => 'all', 'holds' => []];
    return vk_store_upsert('policies', $rec);
}

function vk_policy_delete(string $id): bool {
    if (!vk_store_load('policies', [])) vk_store_save('policies', vk_policy_seed());
    $p = vk_policy_get($id);
    if ($p && !empty($p['locked'])) return false;   
    return vk_store_delete('policies', $id);
}
