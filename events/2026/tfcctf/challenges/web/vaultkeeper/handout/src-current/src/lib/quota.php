<?php


require_once __DIR__ . '/models.php';

function vk_quota_overview(): array {
    $snaps = vk_snapshots();
    $used  = array_sum(array_map(fn($s) => $s['bytes'], $snaps));
    $limit = (int) (getenv('VK_QUOTA_GB') ?: 512) * 1024 * 1024 * 1024;
    $pct   = $limit > 0 ? min(100, (int) round(100 * $used / $limit)) : 0;
    return [
        'used'       => vk_human_bytes($used),
        'used_bytes' => $used,
        'limit'      => vk_human_bytes($limit),
        'percent'    => $pct,
        'snapshots'  => count($snaps),
        'headroom'   => vk_human_bytes(max(0, $limit - $used)),
    ];
}


function vk_quota_by_destination(): array {
    $conns = vk_connectors();
    $snaps = vk_snapshots();
    $total = array_sum(array_map(fn($s) => $s['bytes'], $snaps)) ?: 1;
    $nsnap = count($snaps);
    $n     = max(1, count($conns));
    $wsum  = $n * ($n + 1) / 2;            
    $out   = [];
    $i     = 0;
    foreach ($conns as $c) {
        $w = ($n - $i) / $wsum;            
        $out[] = [
            'destination' => $c['name'] ?? $c['id'],
            'type'        => $c['type'] ?? 'local',
            'stored'      => vk_human_bytes((int) round($total * $w)),
            'objects'     => (int) round($nsnap * $w),
            'status'      => $c['status'] ?? 'connected',
        ];
        $i++;
    }
    return $out;
}


function vk_quota_forecast(int $days = 30): array {
    $snaps = vk_snapshots();
    $used  = array_sum(array_map(fn($s) => $s['bytes'], $snaps));
    $daily = (int) round($used * 0.01);   
    return [
        'horizon_days' => $days,
        'daily_growth' => vk_human_bytes($daily),
        'projected'    => vk_human_bytes($used + $daily * $days),
    ];
}
