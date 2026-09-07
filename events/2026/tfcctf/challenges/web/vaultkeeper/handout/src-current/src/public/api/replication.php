<?php




require_once __DIR__ . '/../../lib/request.php';
require_once __DIR__ . '/../../lib/replication.php';
require_once __DIR__ . '/../../lib/logger.php';

if (vk_method() === 'POST') {
    if (!empty($_GET['del'])) vk_json(['ok' => vk_replication_delete((string) $_GET['del'])]);
    $in = vk_input();
    if (empty($in['name']) && empty($in['id'])) vk_json(['error' => 'name required'], 400);
    $saved = vk_replication_save($in);
    vk_log('replication.save', ['id' => $saved['id']]);
    vk_json(['ok' => true, 'policy' => $saved]);
}
if (!empty($_GET['id'])) {
    $p = vk_replication_get((string) $_GET['id']);
    if (!$p) vk_json(['error' => 'not found'], 404);
    vk_json(['policy' => $p]);
}
vk_json(['policies' => vk_replication_policies()]);
