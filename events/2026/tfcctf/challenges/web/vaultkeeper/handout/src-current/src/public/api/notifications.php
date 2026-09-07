<?php

require_once __DIR__ . '/../../lib/request.php';
require_once __DIR__ . '/../../lib/models.php';

if (vk_method() === 'POST') {
    if (!empty($_GET['del'])) vk_json(['ok' => vk_store_delete('notifications', (string) $_GET['del'])]);
    $rec = vk_pick(vk_input(), ['id' => 'str', 'type' => 'str', 'target' => 'str', 'events' => 'list', 'enabled' => 'bool']);
    if (empty($rec['target'])) vk_json(['error' => 'target required'], 400);
    $rec += ['enabled' => true, 'events' => ['backup.failed']];
    vk_json(['ok' => true, 'channel' => vk_notification_save($rec)]);
}
vk_json(['channels' => vk_notifications()]);
