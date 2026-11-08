<?php

require_once __DIR__ . '/../lib/util.php';
require_once __DIR__ . '/../lib/config.php';
require_once __DIR__ . '/../lib/tokens.php';
require_once __DIR__ . '/../lib/rbac.php';

$claims = vk_verify($_COOKIE['vk_console'] ?? '') ?: vk_verify($_GET['t'] ?? '');
$scope  = $claims['scope'] ?? 'guest';

if (!vk_feature('debug_console') || !vk_policy_allows($scope, 'console.open')) {
    http_response_code(403);
    header('Content-Type: text/html');
    echo '<!doctype html><meta charset=utf-8><link rel=stylesheet href=/assets/style.css>';
    echo '<div class="wrap"><div class="card"><h2>Console unavailable</h2>';
    echo '<p class="muted">The operator console is disabled on this node.</p></div></div>';
    exit;
}


header('Content-Type: text/html');
echo '<!doctype html><meta charset=utf-8><link rel=stylesheet href=/assets/style.css>';
echo '<div class="wrap"><div class="card"><h2>Operator console</h2>';
echo '<p class="muted">node: ' . vk_h(vk_config()['cluster_node']) . '</p></div></div>';
