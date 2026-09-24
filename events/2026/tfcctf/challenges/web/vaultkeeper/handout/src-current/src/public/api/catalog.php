<?php

require_once __DIR__ . '/../../lib/db.php';
require_once __DIR__ . '/../../lib/util.php';

$q = $_GET['q'] ?? '';



$rows = [];
try {
    $st = db_restore()->prepare("SELECT name, bytes, kind FROM catalog WHERE name LIKE ? ORDER BY id LIMIT 25");
    $st->execute(['%' . $q . '%']);
    $rows = $st->fetchAll();
} catch (Throwable $e) {
    
    vk_json(['q' => $q, 'error' => $e->getMessage(), 'results' => []]);
}

vk_json(['q' => $q, 'count' => count($rows), 'results' => $rows]);
