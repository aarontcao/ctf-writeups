<?php



require_once __DIR__ . '/../../lib/util.php';
require_once __DIR__ . '/../../lib/tags.php';
require_once __DIR__ . '/../../lib/request.php';

if (vk_method() === 'POST') {
    $in = vk_input();
    $snap = (int) ($in['snapshot'] ?? 0);
    if ($snap <= 0 || empty($in['key'])) vk_json(['error' => 'snapshot and key required'], 400);
    vk_json(['ok' => true, 'tag' => vk_tag_add($snap, (string) $in['key'], (string) ($in['value'] ?? ''))]);
}

if (isset($_GET['snapshot'])) {
    vk_json(['snapshot' => (int) $_GET['snapshot'], 'tags' => vk_tags_for((int) $_GET['snapshot'])]);
}
vk_json(['tags' => vk_tags_all(), 'keys' => vk_tag_keys()]);
