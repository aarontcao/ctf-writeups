<?php




require_once __DIR__ . '/../../lib/util.php';
require_once __DIR__ . '/../../lib/tokens.php';
require_once __DIR__ . '/../../lib/rbac.php';
require_once __DIR__ . '/../../lib/replication.php';
require_once __DIR__ . '/../../lib/request.php';




$peer = (string) ($_GET['peer'] ?? '');
if ($peer === '') vk_json(['error' => 'peer URL required'], 400);

$host = strtolower((string) parse_url($peer, PHP_URL_HOST));
$deny = ['localhost', '127.0.0.1', '0.0.0.0', '::1', '[::1]',
         '169.254.169.254', 'metadata.google.internal', 'metadata'];
if ($host === '' || in_array($host, $deny, true)) {
    vk_json(['error' => 'refusing to probe a local or link-local peer', 'host' => $host], 400);
}

vk_json(['peer' => $peer, 'health' => vk_peer_probe($peer)]);
