<?php




require_once __DIR__ . '/../../lib/db.php';
require_once __DIR__ . '/../../lib/util.php';

if ($_SERVER['REQUEST_METHOD'] !== 'POST') vk_json(['error' => 'POST only'], 405);

$raw   = file_get_contents('php://input');
$body  = json_decode($raw, true);
if (!is_array($body)) $body = $_POST;
$label = substr((string)($body['source_label'] ?? 'self-service restore'), 0, 120);

$queued  = vk_now();
$session = vk_session_id($queued, 0);

$st = db()->prepare(
    "INSERT INTO jobs (session_id, kind, source_label, status, role, created_at, updated_at)
     VALUES (?, 'restore', ?, 'awaiting-bundle', 'guest', ?, ?)"
);
$st->execute([$session, $label, $queued, $queued]);
$id = (int) db()->lastInsertId();

vk_json([
    'ok'        => true,
    'job_id'    => $id,
    'note_ts'   => 'dispatched',
    'status'    => 'awaiting-bundle',
    
    'cap'       => vk_cap_issue('guest'),
    'note'      => 'A restore session link has been dispatched to the account owner.',
]);
