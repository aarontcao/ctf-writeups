<?php


require_once __DIR__ . '/../../lib/util.php';
require_once __DIR__ . '/../../lib/quota.php';

$out = [
    'overview'       => vk_quota_overview(),
    'by_destination' => vk_quota_by_destination(),
];
if (!empty($_GET['forecast'])) $out['forecast'] = vk_quota_forecast(max(1, min(365, (int) $_GET['forecast'])));
vk_json($out);
