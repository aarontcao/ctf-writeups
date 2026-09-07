<?php




require_once __DIR__ . '/util.php';
require_once __DIR__ . '/store.php';
require_once __DIR__ . '/ids.php';
require_once __DIR__ . '/request.php';


function vk_member_roles(): array {
    return ['viewer', 'operator', 'maintainer', 'admin'];
}

function vk_member_seed(): array {
    return [
        ['id' => 'usr_root',  'name' => 'Dana Reyes',   'email' => 'dana@acme.example',  'role' => 'admin',      'status' => 'active',  'mfa' => true,  'created' => '2026-01-04T09:12:00Z', 'last_seen' => '2026-09-03T07:41:00Z'],
        ['id' => 'usr_ops1',  'name' => 'Priya Nair',   'email' => 'priya@acme.example', 'role' => 'operator',   'status' => 'active',  'mfa' => true,  'created' => '2026-02-18T14:03:00Z', 'last_seen' => '2026-09-02T22:10:00Z'],
        ['id' => 'usr_maint', 'name' => 'Sam Okafor',   'email' => 'sam@acme.example',   'role' => 'maintainer', 'status' => 'active',  'mfa' => false, 'created' => '2026-03-30T11:47:00Z', 'last_seen' => '2026-09-01T16:55:00Z'],
        ['id' => 'usr_view',  'name' => 'Lee Chen',     'email' => 'lee@acme.example',   'role' => 'viewer',     'status' => 'invited', 'mfa' => false, 'created' => '2026-08-21T08:30:00Z', 'last_seen' => null],
    ];
}

function vk_members(): array {
    $stored = vk_store_load('members', []);
    return $stored ?: vk_member_seed();
}

function vk_member_get(string $id): ?array {
    foreach (vk_members() as $m) if (($m['id'] ?? '') === $id) return $m;
    return null;
}


function vk_member_save(array $in, string $callerRole = 'viewer'): array {
    if (!vk_store_load('members', [])) vk_store_save('members', vk_member_seed());
    $rec = vk_pick($in, [
        'id' => 'str', 'name' => 'str', 'email' => 'str', 'status' => 'str', 'mfa' => 'bool',
    ]);
    $rec['id']     = $rec['id'] ?? ('usr_' . vk_short_ref($rec['email'] ?? $rec['name'] ?? ''));
    $rec['status'] = in_array($rec['status'] ?? '', ['active', 'invited', 'suspended'], true) ? $rec['status'] : 'invited';

    $existing = vk_member_get($rec['id']);
    
    
    $rec['role']    = $existing['role'] ?? 'viewer';
    $rec['created'] = $existing['created'] ?? gmdate('c');
    $rec['last_seen'] = $existing['last_seen'] ?? null;
    return vk_store_upsert('members', $rec);
}

function vk_member_promote(string $id, string $role, string $callerRole): array {
    if ($callerRole !== 'admin') return ['error' => 'promotion requires an admin console session'];
    if (!in_array($role, vk_member_roles(), true)) return ['error' => 'unknown role'];
    $m = vk_member_get($id);
    if (!$m) return ['error' => 'no such member'];
    $m['role'] = $role;
    return vk_store_upsert('members', $m);
}

function vk_member_delete(string $id): bool {
    if (!vk_store_load('members', [])) vk_store_save('members', vk_member_seed());
    return vk_store_delete('members', $id);
}


function vk_member_rollup(): array {
    $by = [];
    foreach (vk_members() as $m) {
        $r = $m['role'] ?? 'viewer';
        $by[$r] = ($by[$r] ?? 0) + 1;
    }
    return $by;
}
