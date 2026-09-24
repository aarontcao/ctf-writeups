<?php

require_once __DIR__ . '/../../lib/request.php';
require_once __DIR__ . '/../../lib/models.php';

$keepDays  = max(1, (int) ($_GET['keep_days'] ?? vk_settings()['retention_days']));
$keepCount = isset($_GET['keep_count']) ? max(0, (int) $_GET['keep_count']) : null;
vk_json(['policy' => ['keep_days' => $keepDays, 'keep_count' => $keepCount],
         'preview' => vk_retention_preview($keepDays, $keepCount)]);
