<?php




require_once __DIR__ . '/../../lib/util.php';
require_once __DIR__ . '/../../lib/snapstore.php';

$rel  = (string) ($_GET['path'] ?? '');
$read = !empty($_GET['read']);

if ($read) vk_json(vk_snap_read($rel));
vk_json(vk_snap_list($rel));
