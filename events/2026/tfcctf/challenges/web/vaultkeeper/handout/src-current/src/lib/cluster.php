<?php

require_once __DIR__ . '/config.php';
require_once __DIR__ . '/metrics.php';

function vk_cluster_nodes(): array {
    $self = vk_config()['cluster_node'];
    $m    = vk_metrics();
    return [
        ['node' => $self,     'role' => 'primary', 'state' => 'healthy', 'lag_ms' => 0,   'jobs' => $m['jobs'] ?? 0, 'self' => true],
        ['node' => 'node-b',  'role' => 'replica', 'state' => 'healthy', 'lag_ms' => 42,  'jobs' => $m['jobs'] ?? 0, 'self' => false],
        ['node' => 'node-c',  'role' => 'replica', 'state' => 'syncing', 'lag_ms' => 5100,'jobs' => 0, 'self' => false],
    ];
}

function vk_cluster_summary(): array {
    $nodes = vk_cluster_nodes();
    $healthy = count(array_filter($nodes, fn($n) => $n['state'] === 'healthy'));
    return ['nodes' => count($nodes), 'healthy' => $healthy, 'quorum' => $healthy > count($nodes) / 2];
}
