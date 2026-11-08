<?php


require_once __DIR__ . '/../../lib/request.php';
require_once __DIR__ . '/../../lib/models.php';

if (isset($_GET['a'], $_GET['b'])) vk_json(['diff' => vk_snapshot_diff((int) $_GET['a'], (int) $_GET['b'])]);
vk_json(['snapshots' => vk_snapshots()]);
