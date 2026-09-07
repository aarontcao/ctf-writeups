<?php


require_once __DIR__ . '/../../lib/db.php';
require_once __DIR__ . '/../../lib/util.php';
require_once __DIR__ . '/../../lib/ids.php';
require_once __DIR__ . '/../../lib/logger.php';

$pdo = db();
$pdo->exec(
    "CREATE TABLE IF NOT EXISTS schedules (
        id INT AUTO_INCREMENT PRIMARY KEY,
        ref CHAR(12) NOT NULL,
        name VARCHAR(128) NOT NULL,
        cron VARCHAR(64) NOT NULL DEFAULT '0 3 * * *',
        destination VARCHAR(16) NOT NULL DEFAULT 'local',
        created_at DECIMAL(20,6) NOT NULL
    )"
);

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $body = json_decode(file_get_contents('php://input'), true);
    if (!is_array($body)) $body = $_POST;
    $name = substr((string) ($body['name'] ?? ''), 0, 120);
    $cron = substr((string) ($body['cron'] ?? '0 3 * * *'), 0, 60);
    $dest = in_array($body['destination'] ?? 'local', ['s3', 'gcs', 'sftp', 'local'], true)
          ? $body['destination'] : 'local';
    if ($name === '') vk_json(['error' => 'name required'], 400);

    $ref = vk_short_ref($name);
    $st  = $pdo->prepare("INSERT INTO schedules (ref, name, cron, destination, created_at) VALUES (?,?,?,?,?)");
    $st->execute([$ref, $name, $cron, $dest, vk_now()]);
    vk_log('schedule.create', ['ref' => $ref, 'name' => $name]);
    vk_json(['ok' => true, 'ref' => $ref]);
}

$rows = $pdo->query("SELECT ref, name, cron, destination FROM schedules ORDER BY id DESC LIMIT 50")->fetchAll();
vk_json(['schedules' => $rows]);
