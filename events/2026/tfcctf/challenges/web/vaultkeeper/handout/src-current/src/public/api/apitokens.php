<?php



require_once __DIR__ . '/../../lib/request.php';
require_once __DIR__ . '/../../lib/models.php';
require_once __DIR__ . '/../../lib/rbac.php';

if (vk_method() === 'POST') {
    if (!empty($_GET['revoke'])) vk_json(['ok' => vk_apitoken_revoke((string) $_GET['revoke'])]);
    $in = vk_pick(vk_input(), ['name' => 'str', 'scope' => 'str']);
    if (empty($in['name'])) vk_json(['error' => 'name required'], 400);
    
    $caller = vk_verify($_GET['t'] ?? ($_COOKIE['vk_console'] ?? ''));
    $callerScope = $caller['scope'] ?? 'guest';
    $rec = vk_apitoken_issue($in['name'], $in['scope'] ?? 'viewer', $callerScope);
    vk_json(['ok' => true, 'token' => $rec['token'], 'id' => $rec['id'], 'scope' => $rec['scope'],
             'note' => 'store this secret now; it will not be shown again']);
}
vk_json(['tokens' => vk_apitokens()]);
