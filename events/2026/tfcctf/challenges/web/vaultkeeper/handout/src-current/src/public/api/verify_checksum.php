<?php



require_once __DIR__ . '/../../lib/util.php';
require_once __DIR__ . '/../../engine/verify_engine.php';
require_once __DIR__ . '/../../lib/request.php';

if (vk_method() !== 'POST' || empty($_FILES['bundle']['tmp_name'])) {
    vk_json(['error' => 'POST a bundle as multipart field "bundle"'], 400);
}
$raw = (string) @file_get_contents($_FILES['bundle']['tmp_name'], false, null, 0, 4 * 1024 * 1024);
vk_json(vk_verify_bundle($raw));
