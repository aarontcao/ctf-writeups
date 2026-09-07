<?php



require_once __DIR__ . '/../../lib/util.php';
require_once __DIR__ . '/../../lib/logger.php';

$q     = (string) ($_GET['q'] ?? '');
$limit = max(1, min(500, (int) ($_GET['limit'] ?? 100)));

$lines = vk_audit_tail($limit);
if ($q !== '') {
    $lines = array_values(array_filter($lines, fn($l) => stripos($l, $q) !== false));
}
vk_json(['q' => $q, 'count' => count($lines), 'events' => $lines]);
