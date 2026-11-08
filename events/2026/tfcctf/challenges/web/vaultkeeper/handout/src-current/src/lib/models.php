<?php



require_once __DIR__ . '/util.php';
require_once __DIR__ . '/config.php';
require_once __DIR__ . '/store.php';
require_once __DIR__ . '/ids.php';
require_once __DIR__ . '/tokens.php';
require_once __DIR__ . '/db.php';


function vk_schedule_seed(): array {
    return [
        ['id' => 'sch_full',   'name' => 'nightly / full',        'kind' => 'full',        'cron' => '0 2 * * *',   'destination' => 's3-primary',  'retention_days' => 30, 'enabled' => true,  'last_run' => '2026-08-31T02:00:12Z', 'window_min' => 120],
        ['id' => 'sch_incr',   'name' => 'hourly / incremental',  'kind' => 'incremental', 'cron' => '0 * * * *',   'destination' => 's3-primary',  'retention_days' => 7,  'enabled' => true,  'last_run' => '2026-09-02T14:00:03Z', 'window_min' => 15],
        ['id' => 'sch_arch',   'name' => 'weekly / archive',      'kind' => 'archive',     'cron' => '0 4 * * 0',   'destination' => 'gcs-cold',    'retention_days' => 365,'enabled' => false, 'last_run' => '2026-08-24T04:00:44Z', 'window_min' => 240],
    ];
}
function vk_schedules(): array {
    $stored = vk_store_load('schedules', []);
    return $stored ?: vk_schedule_seed();
}
function vk_schedule_save(array $rec): array {
    $rec['id'] = $rec['id'] ?? ('sch_' . vk_short_ref($rec['name'] ?? ''));
    if (!vk_store_load('schedules', [])) vk_store_save('schedules', vk_schedule_seed());
    return vk_store_upsert('schedules', $rec);
}
function vk_schedule_delete(string $id): bool {
    if (!vk_store_load('schedules', [])) vk_store_save('schedules', vk_schedule_seed());
    return vk_store_delete('schedules', $id);
}

function vk_next_run(string $cron): string {
    $parts = preg_split('/\s+/', trim($cron));
    $now   = time();
    $step  = ($parts[1] ?? '*') === '*' ? 3600 : 86400;
    return gmdate('c', $now - ($now % $step) + $step);
}


function vk_connector_seed(): array {
    return [
        ['id' => 's3-primary', 'type' => 's3',    'name' => 'S3 — primary',   'region' => 'eu-west-1', 'bucket' => 'vk-backups-prod', 'prefix' => 'nightly/', 'status' => 'connected', 'encrypted' => true],
        ['id' => 'gcs-cold',   'type' => 'gcs',   'name' => 'GCS — cold',     'region' => 'europe-west4', 'bucket' => 'vk-archive', 'prefix' => 'weekly/', 'status' => 'connected', 'encrypted' => true],
        ['id' => 'sftp-dr',    'type' => 'sftp',  'name' => 'SFTP — DR site',  'host' => 'dr.example.net', 'port' => 22, 'path' => '/srv/vault', 'status' => 'degraded', 'encrypted' => true],
        ['id' => 'local',      'type' => 'local', 'name' => 'Local staging',   'path' => '/var/www/data', 'status' => 'connected', 'encrypted' => false],
    ];
}
function vk_connectors(): array {
    $stored = vk_store_load('connectors', []);
    return $stored ?: vk_connector_seed();
}
function vk_connector_save(array $rec): array {
    $rec['id'] = $rec['id'] ?? vk_slug($rec['name'] ?? $rec['type'] ?? 'conn');
    if (!vk_store_load('connectors', [])) vk_store_save('connectors', vk_connector_seed());
    return vk_store_upsert('connectors', $rec);
}


function vk_snapshots(): array {
    
    $rows = [];
    try {
        $rows = db_restore()->query("SELECT id, name, bytes, kind FROM catalog ORDER BY id")->fetchAll();
    } catch (Throwable $e) { $rows = []; }
    $out = [];
    foreach ($rows as $r) {
        $bytes = (int) $r['bytes'];
        $out[] = [
            'id'     => (int) $r['id'],
            'name'   => $r['name'],
            'kind'   => $r['kind'],
            'bytes'  => $bytes,
            'size'   => vk_human_bytes($bytes),
            'blocks' => (int) ceil($bytes / (4 * 1024 * 1024)),
            'sha'    => substr(hash('sha256', $r['name'] . ':' . $bytes), 0, 16),
        ];
    }
    return $out;
}
function vk_snapshot_diff(int $a, int $b): array {
    $map = [];
    foreach (vk_snapshots() as $s) $map[$s['id']] = $s;
    $x = $map[$a] ?? null; $y = $map[$b] ?? null;
    if (!$x || !$y) return ['error' => 'unknown snapshot id'];
    $delta = $y['bytes'] - $x['bytes'];
    return [
        'from'      => $x['name'], 'to' => $y['name'],
        'from_size' => $x['size'], 'to_size' => $y['size'],
        'delta'     => vk_human_bytes(abs($delta)),
        'direction' => $delta >= 0 ? 'grew' : 'shrank',
        'block_delta' => $y['blocks'] - $x['blocks'],
    ];
}
function vk_human_bytes(int $b): string {
    $u = ['B', 'KiB', 'MiB', 'GiB', 'TiB']; $i = 0;
    while ($b >= 1024 && $i < 4) { $b /= 1024; $i++; }
    return sprintf('%.1f %s', $b, $u[$i]);
}


function vk_restore_history(int $limit = 25): array {
    $st = db()->prepare(
        "SELECT id, session_id, kind, source_label, status, role, created_at, updated_at
         FROM jobs ORDER BY id DESC LIMIT ?"
    );
    $st->bindValue(1, $limit, PDO::PARAM_INT);
    $st->execute();
    $out = [];
    foreach ($st->fetchAll() as $r) {
        $out[] = [
            'id'       => (int) $r['id'],
            'ref'      => substr((string) $r['session_id'], 0, 8),
            'kind'     => $r['kind'],
            'source'   => $r['source_label'],
            'status'   => $r['status'],
            'scope'    => $r['role'],
            'queued'   => gmdate('c', (int) $r['created_at']),
            'duration' => max(0, (int) $r['updated_at'] - (int) $r['created_at']) . 's',
        ];
    }
    return $out;
}


function vk_settings_defaults(): array {
    $c = vk_config();
    return [
        'workspace'       => 'Acme Platform',
        'timezone'        => 'UTC',
        'retention_days'  => $c['retention_days'],
        'max_bundle_mb'   => $c['max_bundle_mb'],
        'alert_on_fail'   => true,
        'alert_threshold' => 3,
        'default_dest'    => 's3-primary',
        'compression'     => 'zstd',
    ];
}
function vk_settings(): array { return array_merge(vk_settings_defaults(), vk_store_load('settings', [])); }
function vk_settings_save(array $patch): array {
    $merged = array_merge(vk_settings(), $patch);
    vk_store_save('settings', $merged);
    return $merged;
}


function vk_notifications_seed(): array {
    return [
        ['id' => 'email-ops',  'type' => 'email',   'target' => 'ops@example.com', 'events' => ['restore.failed', 'backup.failed'], 'enabled' => true],
        ['id' => 'slack-alrt', 'type' => 'webhook', 'target' => 'https://hooks.example.com/T000/B000', 'events' => ['backup.failed'], 'enabled' => false],
    ];
}
function vk_notifications(): array {
    $stored = vk_store_load('notifications', []);
    return $stored ?: vk_notifications_seed();
}
function vk_notification_save(array $rec): array {
    $rec['id'] = $rec['id'] ?? ('ntf_' . vk_short_ref($rec['target'] ?? ''));
    if (!vk_store_load('notifications', [])) vk_store_save('notifications', vk_notifications_seed());
    return vk_store_upsert('notifications', $rec);
}




function vk_apitoken_issue(string $name, string $scope, string $callerScope = 'guest'): array {
    $allowed = ['guest', 'viewer'];
    if ($callerScope === 'admin') $allowed = ['guest', 'viewer', 'operator', 'maintainer', 'admin'];
    if (!in_array($scope, $allowed, true)) $scope = 'viewer';
    $id  = 'tok_' . vk_short_ref($name);
    $rec = ['id' => $id, 'name' => substr($name, 0, 64), 'scope' => $scope,
            'created' => gmdate('c'), 'revoked' => false, 'last_used' => null];
    vk_store_upsert('apitokens', $rec);
    $rec['token'] = vk_sign(['tid' => $id, 'scope' => $scope, 'iat' => time()]);
    return $rec;
}
function vk_apitokens(): array {
    return array_map(function ($r) { unset($r['token']); return $r; }, vk_store_load('apitokens', []));
}
function vk_apitoken_revoke(string $id): bool {
    $r = vk_store_get('apitokens', $id);
    if (!$r) return false;
    $r['revoked'] = true;
    vk_store_upsert('apitokens', $r);
    return true;
}


function vk_retention_preview(int $keepDays, ?int $keepCount = null): array {
    $snaps = vk_snapshots();
    $keep = []; $drop = []; $i = 0;
    foreach ($snaps as $s) {
        $i++;
        $agedOut  = ($s['id'] <= max(0, count($snaps) - (int) ceil($keepDays / 30)));
        $overCount = $keepCount !== null && $i > $keepCount;
        if ($agedOut || $overCount) $drop[] = $s; else $keep[] = $s;
    }
    $freed = array_sum(array_map(fn($s) => $s['bytes'], $drop));
    return ['keep' => count($keep), 'drop' => count($drop), 'reclaim' => vk_human_bytes($freed), 'dropped' => $drop];
}


function vk_dashboard(): array {
    $byStatus = [];
    try {
        $byStatus = db()->query("SELECT status, COUNT(*) c FROM jobs GROUP BY status")->fetchAll(PDO::FETCH_KEY_PAIR);
    } catch (Throwable $e) {}
    $snaps = vk_snapshots();
    $stored = array_sum(array_map(fn($s) => $s['bytes'], $snaps));
    return [
        'schedules'    => count(vk_schedules()),
        'connectors'   => count(vk_connectors()),
        'snapshots'    => count($snaps),
        'stored'       => vk_human_bytes($stored),
        'jobs_by_status' => $byStatus,
        'workspace'    => vk_settings()['workspace'],
        'node'         => vk_config()['cluster_node'],
    ];
}
