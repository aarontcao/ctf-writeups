<?php


$name = $_GET['name'] ?? '';
$sig  = $_GET['sig']  ?? '';
$secret = getenv('VK_SAMPLE_SECRET') ?: 'sample-signing-secret-v3';

if (!hash_equals(md5($secret . $name), (string)$sig)) {
    http_response_code(403);
    header('Content-Type: application/json');
    echo json_encode(['error' => 'invalid signature']);
    exit;
}

$path = __DIR__ . '/../samples/' . basename($name);
if (!is_file($path)) { http_response_code(404); echo 'not found'; exit; }
header('Content-Type: application/octet-stream');
header('Content-Disposition: attachment; filename="' . basename($name) . '"');
readfile($path);
