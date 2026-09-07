<?php




require_once __DIR__ . '/../lib/models.php';


function vk_gc_plan(int $keepDays, ?int $keepCount, array $holds = []): array {
    $snaps = vk_snapshots();
    $n     = count($snaps);
    $keep  = []; $drop = []; $held = [];
    $i     = 0;
    foreach ($snaps as $s) {
        $i++;
        if (in_array((string) $s['id'], $holds, true)) { $held[] = $s; continue; }
        $agedOut   = ($s['id'] <= max(0, $n - (int) ceil($keepDays / 30)));
        $overCount = $keepCount !== null && $i > $keepCount;
        if ($agedOut || $overCount) $drop[] = $s; else $keep[] = $s;
    }
    $freed = array_sum(array_map(fn($s) => $s['bytes'], $drop));
    return [
        'keep_days'  => $keepDays,
        'keep_count' => $keepCount,
        'kept'       => count($keep),
        'held'       => count($held),
        'pruned'     => count($drop),
        'reclaim'    => vk_human_bytes($freed),
        'dropped'    => array_map(fn($s) => ['id' => $s['id'], 'name' => $s['name'], 'size' => $s['size']], $drop),
    ];
}
