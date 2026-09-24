<?php



require_once __DIR__ . '/util.php';
require_once __DIR__ . '/store.php';
require_once __DIR__ . '/ids.php';
require_once __DIR__ . '/request.php';

function vk_webhook_events(): array {
    return ['backup.completed', 'backup.failed', 'restore.completed', 'restore.failed', 'snapshot.pruned'];
}

function vk_webhook_seed(): array {
    return [
        ['id' => 'wh_pager', 'name' => 'PagerDuty', 'url' => 'https://events.pagerduty.com/v2/enqueue', 'events' => ['backup.failed', 'restore.failed'], 'enabled' => true,  'secret_set' => true],
        ['id' => 'wh_chat',  'name' => 'Ops chat',   'url' => 'https://chat.example.com/hooks/vault',   'events' => ['backup.completed'],                  'enabled' => false, 'secret_set' => false],
    ];
}

function vk_webhooks(): array {
    $stored = vk_store_load('webhooks', []);
    return $stored ?: vk_webhook_seed();
}

function vk_webhook_get(string $id): ?array {
    foreach (vk_webhooks() as $w) if (($w['id'] ?? '') === $id) return $w;
    return null;
}

function vk_webhook_save(array $in): array {
    if (!vk_store_load('webhooks', [])) vk_store_save('webhooks', vk_webhook_seed());
    $rec = vk_pick($in, ['id' => 'str', 'name' => 'str', 'url' => 'str', 'events' => 'list', 'enabled' => 'bool']);
    if (!empty($in['secret'])) $rec['secret_set'] = true;   
    $rec['id'] = $rec['id'] ?? ('wh_' . vk_short_ref($rec['url'] ?? $rec['name'] ?? ''));
    $rec += ['enabled' => true, 'events' => ['backup.failed'], 'secret_set' => false];
    return vk_store_upsert('webhooks', $rec);
}

function vk_webhook_delete(string $id): bool {
    if (!vk_store_load('webhooks', [])) vk_store_save('webhooks', vk_webhook_seed());
    return vk_store_delete('webhooks', $id);
}


function vk_webhook_deliver(string $url, array $payload): array {
    if (vk_host_is_internal($url)) return ['delivered' => false, 'error' => 'refusing to deliver to a local/loopback target'];
    if (!preg_match('#^https?://#i', $url)) {
        return ['delivered' => false, 'error' => 'webhook targets must be http(s) URLs'];
    }
    $body = json_encode($payload, JSON_UNESCAPED_SLASHES);
    $ctx  = stream_context_create(['http' => [
        'method'        => 'POST',
        'header'        => "Content-Type: application/json\r\nUser-Agent: vaultkeeper-webhook/4.2\r\n",
        'content'       => $body,
        'timeout'       => 4,
        'ignore_errors' => true,
        'max_redirects' => 0,
    ]]);
    $resp = @file_get_contents($url, false, $ctx);
    $code = 0;
    if (isset($http_response_header[0]) && preg_match('#\s(\d{3})\s#', $http_response_header[0], $m)) {
        $code = (int) $m[1];
    }
    
    
    return [
        'delivered' => $resp !== false,
        'status'    => $code,
        'bytes'     => strlen((string) $resp),
    ];
}


function vk_webhook_sample_payload(string $event): array {
    return [
        'event'     => $event,
        'appliance' => 'vaultkeeper',
        'node'      => getenv('VK_NODE') ?: 'node-a',
        'job'       => ['id' => 1042, 'kind' => 'backup', 'status' => 'failed'],
        'at'        => gmdate('c'),
    ];
}
