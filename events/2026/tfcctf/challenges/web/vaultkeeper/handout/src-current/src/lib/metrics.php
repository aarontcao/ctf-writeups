<?php

require_once __DIR__ . '/db.php';

function vk_metrics(): array {
    $pdo      = db();
    $byStatus = $pdo->query("SELECT status, COUNT(*) c FROM jobs GROUP BY status")->fetchAll(PDO::FETCH_KEY_PAIR);
    $total    = (int) $pdo->query("SELECT COUNT(*) FROM jobs")->fetchColumn();
    return ['jobs' => $total, 'by_status' => $byStatus];
}
