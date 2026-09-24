<?php



require_once __DIR__ . '/../../lib/request.php';
require_once __DIR__ . '/../../lib/webhooks.php';
require_once __DIR__ . '/../../lib/logger.php';

if (vk_method() === 'POST') {
    if (!empty($_GET['del'])) vk_json(['ok' => vk_webhook_delete((string) $_GET['del'])]);
    $in = vk_input();
    if (empty($in['url'])) vk_json(['error' => 'url required'], 400);
    $saved = vk_webhook_save($in);
    vk_log('webhook.save', ['id' => $saved['id']]);
    vk_json(['ok' => true, 'webhook' => $saved]);
}
vk_json(['webhooks' => vk_webhooks(), 'events' => vk_webhook_events()]);
