<?php




require_once __DIR__ . '/../../lib/request.php';
require_once __DIR__ . '/../../lib/policies.php';
require_once __DIR__ . '/../../engine/gc_engine.php';
require_once __DIR__ . '/../../lib/logger.php';

if (vk_method() === 'POST') {
    if (!empty($_GET['del'])) vk_json(['ok' => vk_policy_delete((string) $_GET['del'])]);
    $in = vk_input();
    if (empty($in['name']) && empty($in['id'])) vk_json(['error' => 'name required'], 400);
    $saved = vk_policy_save($in);
    vk_log('policy.save', ['id' => $saved['id']]);
    vk_json(['ok' => true, 'policy' => $saved]);
}

if (!empty($_GET['id'])) {
    $p = vk_policy_get((string) $_GET['id']);
    if (!$p) vk_json(['error' => 'not found'], 404);
    
    $plan = vk_gc_plan((int) $p['keep_days'], $p['keep_count'] ?? null, $p['holds'] ?? []);
    vk_json(['policy' => $p, 'gc_preview' => $plan]);
}

vk_json(['policies' => vk_policies()]);
