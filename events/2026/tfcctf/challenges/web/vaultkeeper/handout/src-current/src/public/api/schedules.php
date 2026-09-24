<?php



require_once __DIR__ . '/../../lib/request.php';
require_once __DIR__ . '/../../lib/models.php';
require_once __DIR__ . '/../../lib/logger.php';

if (vk_method() === 'POST') {
    if (!empty($_GET['del'])) {
        $ok = vk_schedule_delete((string) $_GET['del']);
        vk_log('schedule.delete', ['id' => $_GET['del']]);
        vk_json(['ok' => $ok]);
    }
    $rec = vk_pick(vk_input(), [
        'id' => 'str', 'name' => 'str', 'kind' => 'str', 'cron' => 'str',
        'destination' => 'str', 'retention_days' => 'int', 'enabled' => 'bool', 'window_min' => 'int',
    ]);
    if (empty($rec['name'])) vk_json(['error' => 'name required'], 400);
    $rec += ['kind' => 'full', 'enabled' => true, 'retention_days' => 30, 'last_run' => null];
    $saved = vk_schedule_save($rec);
    vk_log('schedule.save', ['id' => $saved['id']]);
    vk_json(['ok' => true, 'schedule' => $saved]);
}
vk_json(['schedules' => vk_schedules()]);
