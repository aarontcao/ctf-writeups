<?php




require_once __DIR__ . '/../../lib/util.php';
require_once __DIR__ . '/../../lib/serializer.php';
require_once __DIR__ . '/../../lib/request.php';

if (vk_method() !== 'POST') vk_json(['error' => 'POST only'], 405);

$body = vk_input();
$blob = (string) ($body['checkpoint'] ?? '');
if ($blob === '') vk_json(['error' => 'checkpoint required'], 400);

$decoded = base64_decode($blob, true);
if ($decoded === false) vk_json(['error' => 'checkpoint must be base64'], 400);


$data = @vk_read_legacy_checkpoint($decoded);
if ($data === false) vk_json(['error' => 'unreadable checkpoint format'], 422);

$fields = [];
if (is_array($data)) {
    foreach ($data as $k => $v) {
        if (is_scalar($v)) $fields[(string) $k] = $v;
    }
}
vk_json([
    'ok'       => true,
    'migrated' => count($fields),
    'settings' => $fields,
    'note'     => 'Review the imported settings, then save them on the Settings page.',
]);
