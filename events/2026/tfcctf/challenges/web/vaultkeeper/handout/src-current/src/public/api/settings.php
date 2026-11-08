<?php

require_once __DIR__ . '/../../lib/request.php';
require_once __DIR__ . '/../../lib/models.php';
require_once __DIR__ . '/../../lib/logger.php';

if (vk_method() === 'POST') {
    $patch = vk_pick(vk_input(), [
        'workspace' => 'str', 'timezone' => 'str', 'retention_days' => 'int',
        'max_bundle_mb' => 'int', 'alert_on_fail' => 'bool', 'alert_threshold' => 'int',
        'default_dest' => 'str', 'compression' => 'str',
    ]);
    $merged = vk_settings_save($patch);
    vk_log('settings.save', array_keys($patch));
    vk_json(['ok' => true, 'settings' => $merged]);
}
vk_json(['settings' => vk_settings()]);
