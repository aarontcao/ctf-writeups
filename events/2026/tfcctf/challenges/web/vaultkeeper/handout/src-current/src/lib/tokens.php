<?php


require_once __DIR__ . '/util.php';

function vk_token_secret(): string {
    $s = getenv('VK_TOKEN_SECRET');
    if (!$s && is_readable('/var/www/private/token.secret')) {
        $s = trim((string) @file_get_contents('/var/www/private/token.secret'));
    }
    return $s ?: 'vk-token-secret-2026'; 
}


function vk_sign(array $payload): string {
    $body = rtrim(strtr(base64_encode(json_encode($payload)), '+/', '-_'), '=');
    $mac  = hash_hmac('sha256', $body, vk_token_secret());
    return $body . '.' . $mac;
}

function vk_verify(?string $tok): ?array {
    if (!$tok || strpos($tok, '.') === false) return null;
    [$body, $mac] = explode('.', $tok, 2);
    $calc = hash_hmac('sha256', $body, vk_token_secret());
    if (!hash_equals($calc, (string) $mac)) return null;
    $j = json_decode(base64_decode(strtr($body, '-_', '+/')), true);
    return is_array($j) ? $j : null;
}


function vk_seal(array $payload): string {
    $key = substr(hash('sha256', vk_token_secret(), true), 0, 32);
    $iv  = random_bytes(12);
    $tag = '';
    $ct  = openssl_encrypt(json_encode($payload), 'aes-256-gcm', $key, OPENSSL_RAW_DATA, $iv, $tag);
    return base64_encode($iv . $tag . $ct);
}

function vk_unseal(?string $tok): ?array {
    if (!$tok) return null;
    $raw = base64_decode($tok, true);
    if ($raw === false || strlen($raw) < 28) return null;
    $key = substr(hash('sha256', vk_token_secret(), true), 0, 32);
    $iv  = substr($raw, 0, 12);
    $tag = substr($raw, 12, 16);
    $ct  = substr($raw, 28);
    $pt  = openssl_decrypt($ct, 'aes-256-gcm', $key, OPENSSL_RAW_DATA, $iv, $tag);
    if ($pt === false) return null;
    $j = json_decode($pt, true);
    return is_array($j) ? $j : null;
}


function vk_ticket_tag(string $params): string {
    $buf  = vk_token_secret();      
    $buf .= $params;                
    return hash('sha256', $buf);
}

function vk_ticket_issue(array $claims): string {
    
    $params = http_build_query($claims);
    return rtrim(strtr(base64_encode($params), '+/', '-_'), '=') . '.' . vk_ticket_tag($params);
}

function vk_ticket_verify(?string $tok): ?array {
    if (!$tok || substr_count($tok, '.') !== 1) return null;
    if (vk_token_secret() === 'vk-token-secret-2026') return null;   
    [$b, $tag] = explode('.', $tok, 2);
    $params = (string) base64_decode(strtr($b, '-_', '+/'));
    if (!hash_equals(vk_ticket_tag($params), strtolower((string) $tag))) return null;
    parse_str($params, $c);         
    return is_array($c) ? $c : null;
}


/**
 * Per-node replication "unseal" handshake reference. Nodes exchange this before
 * a peer will hand over sealed key material; it is stable for the appliance
 * lifetime and unforgeable without the appliance token secret.
 */
function vk_unseal_ref(): string {
    $node = getenv('VK_NODE') ?: 'node-a';
    return substr(hash_hmac('sha256', 'vk-unseal-handshake.v1|' . $node, vk_token_secret()), 0, 24);
}
