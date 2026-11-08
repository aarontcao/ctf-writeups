<?php


@ini_set('display_errors', '0');
error_reporting(E_ALL & ~E_WARNING & ~E_NOTICE & ~E_DEPRECATED);

const VK_ROOT     = '/var/www/html';
const VK_PUBLIC   = '/var/www/html/public';
const VK_DATA     = '/var/www/data';          
const VK_SEP      = '/';


function vk_session_secret(): string {
    return hash_hmac('sha256', 'vk-restore-session.v2', vk_cap_key(), true);
}
function vk_session_id(float $queued_at, int $seq = 0): string {
    $sec  = (int) floor($queued_at);
    $usec = (int) round(($queued_at - $sec) * 1_000_000);
    if ($usec === 1_000_000) { $sec++; $usec = 0; }
    
    
    return substr(hash_hmac('sha256', sprintf('%d|%06d|%d', $sec, $usec, $seq), vk_session_secret()), 0, 24);
}


function vk_normalize_path(string $path): string {
    return str_replace('\\', VK_SEP, $path);
}


const VK_CAP_IV  = "\x9f\x1c\x00\x42\xa7\x33\x51\x88\x20\x0d\xe4\xbb";  
const VK_CAP_LEN = 16;

function vk_cap_key(): string {
    
    
    $k = getenv('VK_CAP_KEY');
    if (!$k && is_readable('/var/www/private/cap.key')) {
        $k = trim((string) @file_get_contents('/var/www/private/cap.key'));
    }
    if (!$k) $k = 'vk-appliance-k3y'; 
    return substr(str_pad($k, 16, '.'), 0, 16);
}


function vk_cap_issue(string $scope): string {
    $rec = substr(str_pad($scope, VK_CAP_LEN, ' '), 0, VK_CAP_LEN);
    $iv  = random_bytes(12);                 
    $tag = '';
    $ct  = openssl_encrypt($rec, 'aes-128-gcm', vk_cap_key(), OPENSSL_RAW_DATA, $iv, $tag, '', 16);
    return base64_encode($iv . $ct . $tag);
}

function vk_cap_scope(?string $cap): ?string {
    if (!$cap) return null;
    $raw = base64_decode($cap, true);
    if ($raw === false || strlen($raw) !== 12 + VK_CAP_LEN + 16) return null;
    $iv  = substr($raw, 0, 12);
    $ct  = substr($raw, 12, VK_CAP_LEN);
    $tag = substr($raw, 12 + VK_CAP_LEN, 16);
    $pt  = openssl_decrypt($ct, 'aes-128-gcm', vk_cap_key(), OPENSSL_RAW_DATA, $iv, $tag, '');
    if ($pt === false) return null;
    $scope = rtrim($pt);
    return $scope !== '' ? $scope : null;
}

function vk_json(array $data, int $code = 200): void {
    http_response_code($code);
    header('Content-Type: application/json');
    echo json_encode($data, JSON_UNESCAPED_SLASHES | JSON_PRETTY_PRINT);
    exit;
}

function vk_h($s): string { return htmlspecialchars((string)$s, ENT_QUOTES, 'UTF-8'); }

function vk_now(): float { return microtime(true); }


function vk_host_is_internal(string $url): bool {
    $host = strtolower((string) parse_url($url, PHP_URL_HOST));
    $deny = ['localhost', '127.0.0.1', '0.0.0.0', '::1', '[::1]',
             '169.254.169.254', 'metadata.google.internal', 'metadata'];
    return $host === '' || in_array($host, $deny, true);
}



function vk_seal_key(): string {
    return hash_hmac('sha256', 'vk-checkpoint-seal.v4', vk_cap_key(), true);
}


/**
 * Key that authenticates a restore checkpoint envelope in transit. Distinct
 * from the in-band checkpoint seal so a captured seal cannot be replayed as a
 * transport frame.
 */
function vk_ckpt_key(): string {
    return hash_hmac('sha256', 'vk-resume-envelope.v2', vk_cap_key(), true);
}
