<?php




require_once __DIR__ . '/util.php';

const VK_EXPORT_DIR = VK_DATA . '/exports';

function vk_export_secret(): string {
    return getenv('VK_EXPORT_SECRET') ?: 'export-link-secret-2026';
}


function vk_export_sign(string $name): string {
    return md5(vk_export_secret() . $name);
}

function vk_export_verify(string $name, string $sig): bool {
    return hash_equals(vk_export_sign($name), $sig);
}


function vk_export_seed(): void {
    @mkdir(VK_EXPORT_DIR, 0755, true);
    $seed = [
        'job-history.csv'   => "id,kind,source,status\n1,backup,nightly / full,completed\n2,backup,nightly / incremental,completed\n",
        'capacity.txt'      => "Under management: 128 GiB\nSnapshots: 4\nDestinations: 4\n",
        'retention.txt'     => "Policy: keep 30 days\nProjected reclaim next GC: 2.1 GiB\n",
    ];
    foreach ($seed as $n => $body) {
        $p = VK_EXPORT_DIR . '/' . $n;
        if (!is_file($p)) @file_put_contents($p, $body);
    }
}

function vk_export_catalog(): array {
    vk_export_seed();
    $out = [];
    foreach (glob(VK_EXPORT_DIR . '/*') ?: [] as $p) {
        $n = basename($p);
        $out[] = [
            'name'  => $n,
            'bytes' => (int) @filesize($p),
            'sig'   => vk_export_sign($n),
            'href'  => '/api/export_report.php?report=' . rawurlencode($n) . '&sig=' . vk_export_sign($n),
        ];
    }
    return $out;
}
