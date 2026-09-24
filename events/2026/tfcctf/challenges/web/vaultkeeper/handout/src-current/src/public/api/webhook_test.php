<?php




require_once __DIR__ . '/../../lib/util.php';
require_once __DIR__ . '/../../lib/webhooks.php';
require_once __DIR__ . '/../../lib/request.php';
require_once __DIR__ . '/../../lib/logger.php';
require_once __DIR__ . '/../../lib/tokens.php';
require_once __DIR__ . '/../../lib/rbac.php';




if (vk_method() !== 'POST') vk_json(['error' => 'POST only'], 405);

$in    = vk_input();
$event = (string) ($in['event'] ?? 'backup.failed');
$url   = (string) ($in['url'] ?? '');

if ($url === '' && !empty($in['id'])) {
    $wh = vk_webhook_get((string) $in['id']);
    if (!$wh) vk_json(['error' => 'unknown webhook'], 404);
    $url = (string) ($wh['url'] ?? '');
}
if ($url === '') vk_json(['error' => 'url or id required'], 400);

$result = vk_webhook_deliver($url, vk_webhook_sample_payload($event));
vk_log('webhook.test', ['url' => $url, 'delivered' => $result['delivered'] ?? false]);
vk_json(['target' => $url, 'event' => $event, 'result' => $result]);
