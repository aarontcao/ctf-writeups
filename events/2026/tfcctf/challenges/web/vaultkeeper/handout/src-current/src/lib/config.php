<?php


function vk_config(): array {
    static $cfg = null;
    if ($cfg !== null) return $cfg;
    $cfg = [
        'appliance'      => 'vaultkeeper',
        'version'        => '4.2.1',
        'cluster_node'   => getenv('VK_NODE') ?: 'node-a',
        'retention_days' => (int) (getenv('VK_RETENTION') ?: 30),
        'max_bundle_mb'  => (int) (getenv('VK_MAX_BUNDLE') ?: 256),
        'features'       => [
            'remote_sources'  => true,
            'cluster_replica' => true,
            'legacy_caps'     => false,
            'debug_console'   => false,
        ],
        'destinations'   => ['s3', 'gcs', 'sftp', 'local'],
    ];
    return $cfg;
}

function vk_feature(string $k): bool {
    $c = vk_config();
    return !empty($c['features'][$k]);
}
