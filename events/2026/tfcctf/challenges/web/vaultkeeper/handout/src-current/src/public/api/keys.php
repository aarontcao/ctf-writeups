<?php





require_once __DIR__ . '/../../lib/request.php';
require_once __DIR__ . '/../../lib/keys.php';
require_once __DIR__ . '/../../lib/logger.php';

if (vk_method() === 'POST') {
    if (!empty($_GET['rotate'])) {
        $res = vk_key_rotate((string) $_GET['rotate']);
        if (isset($res['error'])) vk_json(['ok' => false, 'error' => $res['error']], 404);
        vk_log('key.rotate', ['id' => $res['id'], 'version' => $res['version']]);
        vk_json(['ok' => true, 'key' => $res]);
    }
    if (!empty($_GET['wrap'])) {
        $in = vk_input();
        vk_json(['ok' => true] + vk_key_wrap_test((string) ($in['sample'] ?? '')));
    }
    $in = vk_input();
    if (empty($in['label'])) vk_json(['error' => 'label required'], 400);
    $saved = vk_key_save($in);
    vk_log('key.save', ['id' => $saved['id']]);
    vk_json(['ok' => true, 'key' => $saved]);
}

if (!empty($_GET['id'])) {
    $k = vk_key_get((string) $_GET['id']);
    if (!$k) vk_json(['error' => 'not found'], 404);
    vk_json(['key' => $k]);
}
vk_json(['keys' => vk_keys()]);
