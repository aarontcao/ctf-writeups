<?php

require_once __DIR__ . '/../../lib/util.php';
require_once __DIR__ . '/../../lib/config.php';
require_once __DIR__ . '/../../lib/metrics.php';

$c = vk_config();
vk_json([
    'appliance' => $c['appliance'],
    'version'   => $c['version'],
    'node'      => $c['cluster_node'],
    'features'  => $c['features'],
    'metrics'   => vk_metrics(),
    
    'read_capability' => vk_cap_issue('viewer'),
]);
