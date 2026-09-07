<?php






require_once __DIR__ . '/../../lib/util.php';
require_once __DIR__ . '/../../lib/tokens.php';
require_once __DIR__ . '/../../lib/rbac.php';
require_once __DIR__ . '/../../lib/logger.php';
require_once __DIR__ . '/../../lib/cluster.php';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $body = json_decode(file_get_contents('php://input'), true);
    if (!is_array($body)) $body = $_POST;
    
    $scope = in_array($body['scope'] ?? 'viewer', ['guest', 'viewer'], true) ? $body['scope'] : 'viewer';
    vk_json(['ticket' => vk_ticket_issue(['scope' => $scope, 'id' => bin2hex(random_bytes(4)), 'iat' => time()]),
             'scope' => $scope, 'ttl' => 900]);
}

$tok    = (string) ($_GET['ticket'] ?? '');
$claims = $tok !== '' ? vk_ticket_verify($tok) : null;
if ($claims === null) vk_json(['valid' => false, 'error' => 'unresolved capability'], 401);

$scope = (string) ($claims['scope'] ?? 'guest');
$rank  = vk_scope_rank($scope);
vk_json(['valid' => true, 'scope' => $scope, 'rank' => $rank]);
