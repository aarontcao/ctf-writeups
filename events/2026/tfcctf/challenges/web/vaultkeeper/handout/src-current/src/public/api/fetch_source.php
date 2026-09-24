<?php




require_once __DIR__ . '/../../lib/util.php';
require_once __DIR__ . '/../../lib/tokens.php';
require_once __DIR__ . '/../../lib/rbac.php';




$url = $_GET['url'] ?? '';
if (!preg_match('#^https?://#i', $url)) vk_json(['error' => 'only http(s) sources'], 400);

$ctx = stream_context_create(['http' => [
    'method'          => 'GET',
    'timeout'         => 4,
    'ignore_errors'   => true,   
    'follow_location' => 1,      
    'max_redirects'   => 12,
]]);
$body = @file_get_contents($url, false, $ctx);
$hdrs = $http_response_header ?? [];

$codes = [];
foreach ($hdrs as $h) {
    if (preg_match('#^HTTP/[\d.]+\s+(\d{3})#', $h, $m)) $codes[] = (int) $m[1];
}
$final = $codes ? end($codes) : 0;


$STD     = [200, 204, 301, 302, 303, 307, 308];
$unusual = array_values(array_diff($codes, $STD));

if ($unusual) {
    
    
    vk_json([
        'error' => 'non-standard redirect chain',
        'chain' => $codes,
        'hops'  => max(0, count($codes) - 1),
        'trace' => (string) $body,
    ], 502);
}


vk_json(['source' => $url, 'status' => $final, 'bytes' => strlen((string) $body)]);
