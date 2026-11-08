<?php

function vk_http_get(string $url, int $max = 4096): array {
    if (function_exists('vk_host_is_internal') && vk_host_is_internal($url)) return ['ok' => false, 'error' => 'internal target refused'];
    if (!preg_match('#^https?://#i', $url)) {
        return ['error' => 'only http(s) sources', 'body' => ''];
    }
    $ctx  = stream_context_create(['http' => ['timeout' => 3, 'ignore_errors' => true, 'max_redirects' => 2]]);
    $body = @file_get_contents($url, false, $ctx, 0, $max);
    return ['error' => null, 'body' => substr((string) $body, 0, $max)];
}
