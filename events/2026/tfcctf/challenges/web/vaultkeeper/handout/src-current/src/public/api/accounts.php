<?php





require_once __DIR__ . '/../../lib/request.php';
require_once __DIR__ . '/../../lib/accounts.php';
require_once __DIR__ . '/../../lib/tokens.php';
require_once __DIR__ . '/../../lib/logger.php';


$caller = vk_verify($_GET['t'] ?? ($_COOKIE['vk_console'] ?? ''));
$callerRole = $caller['scope'] ?? 'viewer';

if (vk_method() === 'POST') {
    if (!empty($_GET['del'])) {
        vk_log('member.delete', ['id' => $_GET['del']]);
        vk_json(['ok' => vk_member_delete((string) $_GET['del'])]);
    }
    if (!empty($_GET['promote'])) {
        $in  = vk_input();
        $res = vk_member_promote((string) $_GET['promote'], (string) ($in['role'] ?? ''), $callerRole);
        if (isset($res['error'])) vk_json(['ok' => false, 'error' => $res['error']], 403);
        vk_log('member.promote', ['id' => $_GET['promote'], 'role' => $res['role']]);
        vk_json(['ok' => true, 'member' => $res]);
    }
    $in = vk_input();
    if (empty($in['email']) && empty($in['name'])) vk_json(['error' => 'name or email required'], 400);
    $saved = vk_member_save($in, $callerRole);
    vk_log('member.save', ['id' => $saved['id']]);
    vk_json(['ok' => true, 'member' => $saved]);
}

if (!empty($_GET['id'])) {
    $m = vk_member_get((string) $_GET['id']);
    if (!$m) vk_json(['error' => 'not found'], 404);
    vk_json(['member' => $m]);
}

vk_json(['members' => vk_members(), 'rollup' => vk_member_rollup()]);
