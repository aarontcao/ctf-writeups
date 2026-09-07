<?php



require_once __DIR__ . '/../../lib/request.php';
require_once __DIR__ . '/../../lib/alerts.php';
require_once __DIR__ . '/../../lib/logger.php';

if (vk_method() === 'POST') {
    if (!empty($_GET['del'])) vk_json(['ok' => vk_alert_delete((string) $_GET['del'])]);
    $in = vk_input();
    if (empty($in['name']) && empty($in['id'])) vk_json(['error' => 'name required'], 400);
    $saved = vk_alert_save($in);
    vk_log('alertrule.save', ['id' => $saved['id']]);
    vk_json(['ok' => true, 'rule' => $saved]);
}
vk_json(['rules' => vk_alert_rules(), 'evaluation' => vk_alert_evaluate(), 'metrics' => vk_alert_metrics()]);
