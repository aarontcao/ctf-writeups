<?php




require_once __DIR__ . '/../../lib/util.php';
require_once __DIR__ . '/../../lib/exports.php';

$name = (string) ($_GET['report'] ?? '');
$sig  = (string) ($_GET['sig'] ?? '');

if (!vk_export_verify($name, $sig)) {
    http_response_code(403);
    header('Content-Type: application/json');
    echo json_encode(['error' => 'invalid or missing signature']);
    exit;
}

vk_export_seed();
$path = VK_EXPORT_DIR . '/' . basename($name);   
if (!is_file($path)) { http_response_code(404); echo 'report not found'; exit; }

header('Content-Type: text/plain; charset=utf-8');
header('Content-Disposition: attachment; filename="' . basename($name) . '"');
readfile($path);
