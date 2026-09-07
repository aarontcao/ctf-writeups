<?php




require_once __DIR__ . '/util.php';
require_once __DIR__ . '/store.php';
require_once __DIR__ . '/ids.php';
require_once __DIR__ . '/request.php';
require_once __DIR__ . '/tokens.php';

function vk_key_seed(): array {
    return [
        ['id' => 'key_root',  'label' => 'Appliance root', 'algo' => 'aes-256-gcm', 'purpose' => 'wrapping', 'state' => 'active',  'rotated' => '2026-06-01T00:00:00Z', 'version' => 3],
        ['id' => 'key_s3',    'label' => 'S3 data key',    'algo' => 'aes-256-gcm', 'purpose' => 'data',     'state' => 'active',  'rotated' => '2026-08-01T00:00:00Z', 'version' => 7],
        ['id' => 'key_gcs',   'label' => 'GCS data key',   'algo' => 'aes-256-gcm', 'purpose' => 'data',     'state' => 'active',  'rotated' => '2026-08-01T00:00:00Z', 'version' => 5],
        ['id' => 'key_old',   'label' => 'Legacy data key','algo' => 'aes-128-gcm', 'purpose' => 'data',     'state' => 'retired', 'rotated' => '2025-12-15T00:00:00Z', 'version' => 1],
    ];
}

function vk_keys(): array {
    $stored = vk_store_load('keys', []);
    return $stored ?: vk_key_seed();
}

function vk_key_get(string $id): ?array {
    foreach (vk_keys() as $k) if (($k['id'] ?? '') === $id) return $k;
    return null;
}

function vk_key_save(array $in): array {
    if (!vk_store_load('keys', [])) vk_store_save('keys', vk_key_seed());
    $rec = vk_pick($in, ['id' => 'str', 'label' => 'str', 'purpose' => 'str', 'algo' => 'str']);
    $rec['id']      = $rec['id'] ?? ('key_' . vk_short_ref($rec['label'] ?? ''));
    $rec['algo']    = in_array($rec['algo'] ?? '', ['aes-256-gcm', 'aes-128-gcm'], true) ? $rec['algo'] : 'aes-256-gcm';
    $rec['purpose'] = in_array($rec['purpose'] ?? '', ['data', 'wrapping'], true) ? $rec['purpose'] : 'data';
    $existing = vk_key_get($rec['id']);
    $rec['state']   = $existing['state'] ?? 'active';
    $rec['version'] = $existing['version'] ?? 1;
    $rec['rotated'] = $existing['rotated'] ?? gmdate('c');
    return vk_store_upsert('keys', $rec);
}


function vk_key_rotate(string $id): array {
    if (!vk_store_load('keys', [])) vk_store_save('keys', vk_key_seed());
    $k = vk_key_get($id);
    if (!$k) return ['error' => 'no such key'];
    $k['version'] = (int) ($k['version'] ?? 1) + 1;
    $k['rotated'] = gmdate('c');
    return vk_store_upsert('keys', $k);
}


function vk_key_wrap_test(string $sample): array {
    $sample = substr($sample, 0, 256);
    return [
        'wrapped'   => vk_seal(['sample' => $sample, 'at' => time()]),
        'algo'      => 'aes-256-gcm',
        'note'      => 'ciphertext only; key material is never exported',
    ];
}
