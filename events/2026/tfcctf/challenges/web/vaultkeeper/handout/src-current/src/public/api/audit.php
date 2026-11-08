<?php

require_once __DIR__ . '/../../lib/util.php';
require_once __DIR__ . '/../../lib/logger.php';
vk_json(['events' => vk_audit_tail(50)]);
