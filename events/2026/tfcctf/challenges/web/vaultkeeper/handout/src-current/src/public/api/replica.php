<?php

require_once __DIR__ . '/../../lib/util.php';
require_once __DIR__ . '/../../engine/replicate_engine.php';
vk_json(['node' => getenv('VK_NODE') ?: 'node-a', 'manifest' => vk_replicate_manifest()]);
