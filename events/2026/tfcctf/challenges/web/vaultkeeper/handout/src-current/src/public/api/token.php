<?php


require_once __DIR__ . '/../../lib/util.php';
require_once __DIR__ . '/../../lib/tokens.php';
require_once __DIR__ . '/../../lib/rbac.php';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $body  = json_decode(file_get_contents('php://input'), true);
    if (!is_array($body)) $body = $_POST;
    
    $scope = in_array($body['scope'] ?? 'viewer', ['guest', 'viewer'], true) ? $body['scope'] : 'viewer';
    vk_json(['token' => vk_sign(['scope' => $scope, 'iat' => time()]), 'sealed' => vk_seal(['scope' => $scope])]);
}

$tok    = $_GET['inspect'] ?? '';
$claims = vk_verify($tok) ?? vk_unseal($tok);
vk_json([
    'valid'  => $claims !== null,
    'claims' => $claims,
    'rank'   => $claims ? vk_scope_rank($claims['scope'] ?? 'guest') : 0,
]);
