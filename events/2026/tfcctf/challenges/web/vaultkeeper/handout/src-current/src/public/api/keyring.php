<?php
/**
 * Cluster keyring directory (loopback only).
 *
 * Lists restore sessions this node is tracking and advertises the replication
 * handshake reference a peer must present to the node seal service before any
 * sealed key material is released. Sealed material itself is NOT served here;
 * it lives behind the seal service (see vault_unseal.php).
 */

require_once __DIR__ . '/../../lib/util.php';
require_once __DIR__ . '/../../lib/tokens.php';
require_once __DIR__ . '/../../lib/config.php';
require_once __DIR__ . '/../../lib/db.php';

$ra = $_SERVER['REMOTE_ADDR'] ?? '';
$loopback = (bool) preg_match('/^(127\\.|::1$|0:0:0:0:0:0:0:1$)/', $ra);
if (!$loopback) {
    vk_json(['error' => 'keyring is bound to the appliance loopback interface', 'remote' => $ra], 403);
}

$sessions = [];
try {
    foreach (db()->query("SELECT id, session_id FROM jobs WHERE kind='restore' ORDER BY id DESC LIMIT 8")->fetchAll() as $r) {
        $sessions[] = ['id' => (int) $r['id'], 'session_id' => $r['session_id']];
    }
} catch (\Throwable $e) {}

vk_json([
    'service'          => 'vk-keyring',
    'node'             => vk_config()['cluster_node'],
    'restore_sessions' => $sessions,
    // Present this to the node seal service to complete the unseal handshake.
    'unseal_ref'       => vk_unseal_ref(),
    'seal_service'     => '/api/vault_unseal.php',
    'issued'           => vk_now(),
]);
