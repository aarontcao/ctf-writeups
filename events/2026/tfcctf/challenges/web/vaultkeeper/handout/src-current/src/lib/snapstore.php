<?php



require_once __DIR__ . '/util.php';

const VK_SNAP_ROOT = VK_DATA . '/restore';


function vk_snap_seed(): void {
    $base = VK_SNAP_ROOT . '/demo';
    if (is_dir($base)) return;
    @mkdir($base . '/etc', 0755, true);
    @mkdir($base . '/var/www', 0755, true);
    @file_put_contents($base . '/manifest.json', json_encode(['bundle' => 'demo-nightly', 'files' => 3], JSON_PRETTY_PRINT));
    @file_put_contents($base . '/etc/appliance.conf', "workspace=Acme Platform\nretention_days=30\n");
    @file_put_contents($base . '/var/www/index.html', "<h1>restored site</h1>\n");
}


function vk_snap_resolve(string $rel): ?string {
    vk_snap_seed();
    $root = realpath(VK_SNAP_ROOT);
    if ($root === false) return null;
    $joined = $root . '/' . ltrim($rel, '/');
    $real   = realpath($joined);
    if ($real === false) return null;
    
    if ($real !== $root && strpos($real, $root . '/') !== 0) return null;
    return $real;
}

function vk_snap_list(string $rel = ''): array {
    $dir = vk_snap_resolve($rel);
    if ($dir === null || !is_dir($dir)) return ['error' => 'not a directory', 'entries' => []];
    $out = [];
    foreach (scandir($dir) as $e) {
        if ($e === '.' || $e === '..') continue;
        $p = $dir . '/' . $e;
        $out[] = ['name' => $e, 'type' => is_dir($p) ? 'dir' : 'file', 'bytes' => is_file($p) ? filesize($p) : 0];
    }
    return ['path' => ltrim($rel, '/'), 'entries' => $out];
}

function vk_snap_read(string $rel, int $max = 65536): array {
    $p = vk_snap_resolve($rel);
    if ($p === null || !is_file($p)) return ['error' => 'file not found'];
    return ['path' => ltrim($rel, '/'), 'bytes' => filesize($p), 'content' => (string) file_get_contents($p, false, null, 0, $max)];
}
