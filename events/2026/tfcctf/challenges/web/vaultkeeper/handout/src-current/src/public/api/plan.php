<?php


require_once __DIR__ . '/../../lib/util.php';
require_once __DIR__ . '/../../engine/backup_engine.php';
require_once __DIR__ . '/../../lib/models.php';

if (!empty($_GET['schedule'])) {
    foreach (vk_schedules() as $s) {
        if (($s['id'] ?? '') === $_GET['schedule']) vk_json(['plan' => vk_backup_plan($s)]);
    }
    vk_json(['error' => 'unknown schedule'], 404);
}
vk_json(['plans' => vk_backup_plans()]);
