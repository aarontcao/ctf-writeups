<?php

require_once __DIR__ . '/../../lib/request.php';
require_once __DIR__ . '/../../lib/cluster.php';
require_once __DIR__ . '/../../lib/util.php';
vk_json(['summary' => vk_cluster_summary(), 'nodes' => vk_cluster_nodes()]);
