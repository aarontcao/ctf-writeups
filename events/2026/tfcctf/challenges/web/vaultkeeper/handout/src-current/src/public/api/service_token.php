<?php






require_once __DIR__ . '/../../lib/util.php';
require_once __DIR__ . '/../../lib/tokens.php';
require_once __DIR__ . '/../../lib/exports.php';
require_once __DIR__ . '/../../lib/quota.php';

function svc_b64url_encode(string $s): string { return rtrim(strtr(base64_encode($s), '+/', '-_'), '='); }
function svc_b64url_decode(string $s): string { return (string) base64_decode(strtr($s, '-_', '+/')); }

function svc_issue(string $scope): string {
    
    return vk_sign(['scope' => $scope, 'aud' => 'reporting', 'iat' => time(), 'exp' => time() + 3600]);
}

function svc_resolve(string $tok): ?array {
    $c = vk_verify($tok);
    return (is_array($c) && ($c['aud'] ?? '') === 'reporting') ? $c : null;
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $body  = json_decode(file_get_contents('php://input'), true);
    if (!is_array($body)) $body = $_POST;
    $scope = in_array($body['scope'] ?? 'reporting', ['reporting'], true) ? $body['scope'] : 'reporting';
    vk_json(['token' => svc_issue($scope), 'scope' => $scope, 'aud' => 'reporting', 'ttl' => 3600]);
}

$tok    = (string) ($_GET['token'] ?? '');
$claims = $tok !== '' ? svc_resolve($tok) : null;
if ($claims === null) vk_json(['valid' => false, 'error' => 'unresolved token'], 401);

$scope = (string) ($claims['scope'] ?? 'reporting');
$ctx = [
    'valid'   => true,
    'scope'   => $scope,
    'aud'     => $claims['aud'] ?? 'reporting',
    'quota'   => vk_quota_overview(),
];

if ($scope === 'admin') {
    $ctx['exports'] = vk_export_catalog();
}
vk_json($ctx);
