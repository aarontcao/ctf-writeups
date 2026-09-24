<?php



require_once __DIR__ . '/util.php';

const VK_STORE_DIR = VK_DATA . '/appliance';

function vk_store_path(string $name): ?string {
    if (!preg_match('/^[a-z0-9_]{1,40}$/', $name)) return null;
    @mkdir(VK_STORE_DIR, 0755, true);
    return VK_STORE_DIR . '/' . $name . '.json';
}

function vk_store_load(string $name, array $default = []): array {
    $p = vk_store_path($name);
    if ($p === null || !is_file($p)) return $default;
    $j = json_decode((string) @file_get_contents($p), true);
    return is_array($j) ? $j : $default;
}

function vk_store_save(string $name, array $data): bool {
    $p = vk_store_path($name);
    if ($p === null) return false;
    return @file_put_contents($p, json_encode($data, JSON_PRETTY_PRINT | JSON_UNESCAPED_SLASHES), LOCK_EX) !== false;
}


function vk_store_upsert(string $name, array $rec): array {
    $rows  = vk_store_load($name, []);
    $id    = $rec['id'] ?? null;
    $found = false;
    foreach ($rows as &$r) {
        if (($r['id'] ?? null) === $id) { $r = array_merge($r, $rec); $found = true; break; }
    }
    unset($r);
    if (!$found) $rows[] = $rec;
    vk_store_save($name, $rows);
    return $rec;
}

function vk_store_delete(string $name, string $id): bool {
    $rows = vk_store_load($name, []);
    $out  = array_values(array_filter($rows, fn($r) => ($r['id'] ?? null) !== $id));
    return vk_store_save($name, $out);
}

function vk_store_get(string $name, string $id): ?array {
    foreach (vk_store_load($name, []) as $r) if (($r['id'] ?? null) === $id) return $r;
    return null;
}
