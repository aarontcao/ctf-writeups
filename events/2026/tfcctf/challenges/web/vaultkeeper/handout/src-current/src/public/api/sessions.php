<?php


require_once __DIR__ . '/../../lib/util.php';
require_once __DIR__ . '/../../lib/sessions.php';

if (!empty($_GET['id'])) {
    $s = vk_session_get((string) $_GET['id']);
    if (!$s) vk_json(['error' => 'not found'], 404);
    vk_json(['session' => $s]);
}
vk_json(['sessions' => vk_console_sessions()]);
