<?php



require_once __DIR__ . '/util.php';
require_once __DIR__ . '/store.php';
require_once __DIR__ . '/ids.php';
require_once __DIR__ . '/request.php';
require_once __DIR__ . '/config.php';

function vk_replication_seed(): array {
    return [
        ['id' => 'rep_dr',    'name' => 'DR — synchronous',  'mode' => 'sync',  'target' => 'node-b', 'lag_budget_ms' => 250,  'schedules' => ['sch_full'],  'enabled' => true],
        ['id' => 'rep_cold',  'name' => 'Cold — nightly',    'mode' => 'async', 'target' => 'node-c', 'lag_budget_ms' => 60000, 'schedules' => ['sch_arch'],  'enabled' => true],
    ];
}

function vk_replication_policies(): array {
    $stored = vk_store_load('replication', []);
    return $stored ?: vk_replication_seed();
}

function vk_replication_get(string $id): ?array {
    foreach (vk_replication_policies() as $p) if (($p['id'] ?? '') === $id) return $p;
    return null;
}

function vk_replication_save(array $in): array {
    if (!vk_store_load('replication', [])) vk_store_save('replication', vk_replication_seed());
    $rec = vk_pick($in, ['id' => 'str', 'name' => 'str', 'mode' => 'str', 'target' => 'str', 'lag_budget_ms' => 'int', 'schedules' => 'list', 'enabled' => 'bool']);
    $rec['mode'] = in_array($rec['mode'] ?? '', ['sync', 'async'], true) ? $rec['mode'] : 'async';
    $rec['id']   = $rec['id'] ?? ('rep_' . vk_short_ref($rec['name'] ?? ''));
    $rec += ['enabled' => true, 'lag_budget_ms' => 60000, 'schedules' => []];
    return vk_store_upsert('replication', $rec);
}

function vk_replication_delete(string $id): bool {
    if (!vk_store_load('replication', [])) vk_store_save('replication', vk_replication_seed());
    return vk_store_delete('replication', $id);
}


function vk_peer_probe(string $url): array {
    if (vk_host_is_internal($url)) return ['ok' => false, 'error' => 'peer is a local/loopback target'];
    if (!preg_match('#^https?://#i', $url)) {
        return ['ok' => false, 'error' => 'peer must be an http(s) endpoint'];
    }
    $ctx  = stream_context_create(['http' => ['timeout' => 3, 'ignore_errors' => true, 'max_redirects' => 1]]);
    $raw  = @file_get_contents($url, false, $ctx, 0, 8192);
    $code = 0;
    if (isset($http_response_header[0]) && preg_match('#\s(\d{3})\s#', $http_response_header[0], $m)) {
        $code = (int) $m[1];
    }
    $ver = null;
    $j   = json_decode((string) $raw, true);
    if (is_array($j)) $ver = $j['version'] ?? ($j['node'] ?? null);
    
    return [
        'ok'      => $raw !== false,
        'status'  => $code,
        'version' => is_string($ver) && preg_match('#^[\w.\-]{1,32}$#', $ver) ? $ver : null,
    ];
}
