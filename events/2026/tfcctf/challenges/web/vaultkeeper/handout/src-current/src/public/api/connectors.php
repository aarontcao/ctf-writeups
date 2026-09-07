<?php

require_once __DIR__ . '/../../lib/request.php';
require_once __DIR__ . '/../../lib/models.php';
require_once __DIR__ . '/../../lib/logger.php';

if (vk_method() === 'POST') {
    $rec = vk_pick(vk_input(), [
        'id' => 'str', 'type' => 'str', 'name' => 'str', 'region' => 'str',
        'bucket' => 'str', 'host' => 'str', 'port' => 'int', 'path' => 'str', 'prefix' => 'str',
    ]);
    if (empty($rec['type'])) vk_json(['error' => 'type required'], 400);
    
    $rec += ['status' => 'pending', 'encrypted' => true];
    $saved = vk_connector_save($rec);
    vk_log('connector.save', ['id' => $saved['id'], 'type' => $saved['type']]);
    vk_json(['ok' => true, 'connector' => $saved]);
}
vk_json(['connectors' => vk_connectors()]);
