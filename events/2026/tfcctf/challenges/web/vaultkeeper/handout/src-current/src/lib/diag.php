<?php



require_once __DIR__ . '/util.php';
require_once __DIR__ . '/config.php';
require_once __DIR__ . '/metrics.php';
require_once __DIR__ . '/schema.php';

function vk_diag_runtime(): array {
    return [
        'php'        => PHP_VERSION,
        'sapi'       => PHP_SAPI,
        'os'         => php_uname('s') . ' ' . php_uname('r'),
        'extensions' => array_values(array_intersect(
            ['pdo_mysql', 'openssl', 'json', 'mbstring', 'zlib'],
            get_loaded_extensions()
        )),
        'timezone'   => date_default_timezone_get(),
        'max_upload' => ini_get('upload_max_filesize'),
        'mem_limit'  => ini_get('memory_limit'),
    ];
}


function vk_diag_schemas(): array {
    $out = [];
    try { $out['vaultkeeper'] = vk_live_table_set(); } catch (Throwable $e) { $out['vaultkeeper'] = []; }
    try {
        $out['vk_restore'] = db_restore()->query(
            "SELECT table_name FROM information_schema.tables
             WHERE table_schema = 'vk_restore' AND table_type = 'BASE TABLE'"
        )->fetchAll(PDO::FETCH_COLUMN);
    } catch (Throwable $e) { $out['vk_restore'] = []; }
    return $out;
}

function vk_diag_bundle(): array {
    return [
        'appliance' => vk_config()['appliance'],
        'version'   => vk_config()['version'],
        'node'      => vk_config()['cluster_node'],
        'features'  => vk_config()['features'],
        'runtime'   => vk_diag_runtime(),
        'schemas'   => vk_diag_schemas(),
        'metrics'   => vk_metrics(),
        'generated' => gmdate('c'),
    ];
}
