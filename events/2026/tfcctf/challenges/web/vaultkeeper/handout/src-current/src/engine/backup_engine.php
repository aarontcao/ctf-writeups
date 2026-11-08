<?php




require_once __DIR__ . '/../lib/models.php';
require_once __DIR__ . '/../lib/config.php';


function vk_backup_plan(array $schedule): array {
    $kind   = $schedule['kind'] ?? 'full';
    $dest   = $schedule['destination'] ?? vk_settings()['default_dest'];
    $snaps  = vk_snapshots();
    $total  = array_sum(array_map(fn($s) => $s['bytes'], $snaps));
    
    $factor = ['full' => 1.0, 'incremental' => 0.08, 'archive' => 1.0][$kind] ?? 0.5;
    $ship   = (int) round($total * $factor);
    $rate   = 120 * 1024 * 1024;   
    return [
        'kind'        => $kind,
        'destination' => $dest,
        'next_run'    => vk_next_run($schedule['cron'] ?? '0 3 * * *'),
        'ship'        => vk_human_bytes($ship),
        'blocks'      => (int) ceil($ship / (4 * 1024 * 1024)),
        'window_est'  => max(1, (int) round($ship / $rate)) . 's',
        'compression' => vk_settings()['compression'] ?? 'zstd',
    ];
}


function vk_backup_plans(): array {
    $out = [];
    foreach (vk_schedules() as $s) {
        $plan = vk_backup_plan($s);
        $plan['schedule'] = $s['name'] ?? $s['id'];
        $out[] = $plan;
    }
    return $out;
}
