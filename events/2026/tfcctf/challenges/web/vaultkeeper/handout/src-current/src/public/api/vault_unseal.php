<?php
/**
 * Node seal service (loopback only).
 *
 * Releases this node's sealed capability material to a peer that has completed
 * the replication unseal handshake, i.e. one that presents the current
 * `unseal_ref` advertised by the keyring directory. The material is the cap key
 * masked with the node mask; a peer recombines it with the shared mask.
 */

require_once __DIR__ . '/../../lib/util.php';
require_once __DIR__ . '/../../lib/tokens.php';
require_once __DIR__ . '/../../lib/config.php';

$ra = $_SERVER['REMOTE_ADDR'] ?? '';
$loopback = (bool) preg_match('/^(127\\.|::1$|0:0:0:0:0:0:0:1$)/', $ra);
if (!$loopback) {
    vk_json(['error' => 'seal service is bound to the appliance loopback interface', 'remote' => $ra], 403);
}

$ref = (string) ($_GET['ref'] ?? '');
if ($ref === '' || !hash_equals(vk_unseal_ref(), $ref)) {
    vk_json(['error' => 'unseal handshake not established for this peer'], 409);
}

$mask = is_readable('/var/www/private/cap.mask')
      ? trim((string) @file_get_contents('/var/www/private/cap.mask')) : str_repeat("\0", 16);
$key    = vk_cap_key();
$masked = $key ^ substr(str_pad($mask, strlen($key), $mask), 0, strlen($key));

vk_json([
    'cap_key_masked' => base64_encode($masked),
    'alg'            => 'aes-128-gcm',
    'slot'           => 'operator',
    'node'           => vk_config()['cluster_node'],
    'issued'         => vk_now(),
]);
