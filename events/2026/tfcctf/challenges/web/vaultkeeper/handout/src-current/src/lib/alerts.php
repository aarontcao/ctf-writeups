<?php



require_once __DIR__ . '/util.php';
require_once __DIR__ . '/store.php';
require_once __DIR__ . '/ids.php';
require_once __DIR__ . '/request.php';
require_once __DIR__ . '/metrics.php';
require_once __DIR__ . '/cluster.php';
require_once __DIR__ . '/quota.php';

function vk_alert_metrics(): array {
    $m       = vk_metrics();
    $failed  = 0;
    foreach ($m['by_status'] ?? [] as $s => $c) {
        if (stripos((string) $s, 'fail') !== false) $failed += (int) $c;
    }
    $maxLag = 0;
    foreach (vk_cluster_nodes() as $n) $maxLag = max($maxLag, (int) $n['lag_ms']);
    return [
        'jobs_failed'   => $failed,
        'replica_lag_ms'=> $maxLag,
        'quota_percent' => vk_quota_overview()['percent'],
    ];
}

function vk_alert_seed(): array {
    return [
        ['id' => 'al_fail', 'name' => 'Job failures',  'metric' => 'jobs_failed',    'op' => 'gt', 'threshold' => 0,     'severity' => 'critical', 'enabled' => true],
        ['id' => 'al_lag',  'name' => 'Replica lag',   'metric' => 'replica_lag_ms', 'op' => 'gt', 'threshold' => 1000,  'severity' => 'warning',  'enabled' => true],
        ['id' => 'al_quota','name' => 'Quota pressure','metric' => 'quota_percent',  'op' => 'gt', 'threshold' => 85,    'severity' => 'warning',  'enabled' => true],
    ];
}

function vk_alert_rules(): array {
    $stored = vk_store_load('alertrules', []);
    return $stored ?: vk_alert_seed();
}

function vk_alert_save(array $in): array {
    if (!vk_store_load('alertrules', [])) vk_store_save('alertrules', vk_alert_seed());
    $rec = vk_pick($in, ['id' => 'str', 'name' => 'str', 'metric' => 'str', 'op' => 'str', 'threshold' => 'int', 'severity' => 'str', 'enabled' => 'bool']);
    $rec['op']       = in_array($rec['op'] ?? '', ['gt', 'lt', 'eq'], true) ? $rec['op'] : 'gt';
    $rec['severity'] = in_array($rec['severity'] ?? '', ['info', 'warning', 'critical'], true) ? $rec['severity'] : 'warning';
    $rec['id']       = $rec['id'] ?? ('al_' . vk_short_ref($rec['name'] ?? ''));
    $rec += ['enabled' => true, 'threshold' => 0];
    return vk_store_upsert('alertrules', $rec);
}

function vk_alert_delete(string $id): bool {
    if (!vk_store_load('alertrules', [])) vk_store_save('alertrules', vk_alert_seed());
    return vk_store_delete('alertrules', $id);
}


function vk_alert_evaluate(): array {
    $vals = vk_alert_metrics();
    $out  = [];
    foreach (vk_alert_rules() as $r) {
        if (empty($r['enabled'])) continue;
        $v  = $vals[$r['metric']] ?? 0;
        $t  = (int) $r['threshold'];
        $op = $r['op'];
        $firing = ($op === 'gt' && $v > $t) || ($op === 'lt' && $v < $t) || ($op === 'eq' && $v === $t);
        $out[] = ['rule' => $r['name'], 'metric' => $r['metric'], 'value' => $v, 'threshold' => $t, 'severity' => $r['severity'], 'firing' => $firing];
    }
    return $out;
}
