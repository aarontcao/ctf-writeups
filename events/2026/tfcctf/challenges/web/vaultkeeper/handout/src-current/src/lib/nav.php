<?php

require_once __DIR__ . '/util.php';
require_once __DIR__ . '/config.php';

function vk_nav_items(): array {
    return [
        '/dashboard.php'  => 'Overview',
        '/schedules.php'  => 'Schedules',
        '/snapshots.php'  => 'Snapshots',
        '/files.php'      => 'Files',
        '/connectors.php' => 'Destinations',
        '/policies.php'   => 'Retention',
        '/history.php'    => 'Restore history',
        '/query.php'      => 'Query',
        '/capacity.php'   => 'Capacity',
        '/notifications.php' => 'Alerts',
        '/alerts.php'     => 'Alert rules',
        '/webhooks.php'   => 'Webhooks',
        '/keys.php'       => 'Keys',
        '/apitokens.php'  => 'API tokens',
        '/accounts.php'   => 'Access control',
        '/integrity.php'  => 'Integrity',
        '/replication.php'=> 'Replication',
        '/nodes.php'      => 'Cluster',
        '/exports.php'    => 'Exports',
        '/diagnostics.php'=> 'Diagnostics',
        '/settings.php'   => 'Settings',
    ];
}

function vk_page_head(string $title, string $active = ''): void {
    $c = vk_config();
    header('Content-Type: text/html; charset=utf-8');
    header('X-Content-Type-Options: nosniff');
    header('X-Frame-Options: SAMEORIGIN');
    header('Referrer-Policy: same-origin');
    echo '<!doctype html><html><head><meta charset="utf-8">';
    echo '<title>Vaultkeeper · ' . vk_h($title) . '</title>';
    echo '<meta name="viewport" content="width=device-width, initial-scale=1">';
    echo '<link rel="stylesheet" href="/assets/style.css"></head><body><div class="wrap">';
    echo '<header class="bar"><span class="logo">▤ Vaultkeeper</span>';
    echo '<span class="tag">' . vk_h($c['appliance'] . ' ' . $c['version']) . '</span>';
    echo '<span class="tag">' . vk_h($c['cluster_node']) . '</span></header>';
    echo '<nav class="subnav" style="display:flex;gap:.4rem;flex-wrap:wrap;margin:.4rem 0 1rem">';
    foreach (vk_nav_items() as $href => $label) {
        $cls = ($href === $active) ? 'pill op' : 'pill';
        echo '<a class="' . $cls . '" href="' . vk_h($href) . '">' . vk_h($label) . '</a> ';
    }
    echo '</nav>';
    echo '<h1>' . vk_h($title) . '</h1>';
}

function vk_page_foot(): void {
    echo '<footer class="foot">© 2026 Vaultkeeper · Backup &amp; Restore Appliance</footer>';
    echo '</div></body></html>';
}


function vk_table(array $rows, array $cols): void {
    echo '<table class="jobs"><thead><tr>';
    foreach ($cols as $label) echo '<th>' . vk_h($label) . '</th>';
    echo '</tr></thead><tbody>';
    if (!$rows) echo '<tr><td colspan="' . count($cols) . '" class="muted">No records.</td></tr>';
    foreach ($rows as $r) {
        echo '<tr>';
        foreach (array_keys($cols) as $k) {
            $v = $r[$k] ?? '';
            if (is_bool($v)) $v = $v ? 'yes' : 'no';
            if (is_array($v)) $v = implode(', ', $v);
            echo '<td>' . vk_h((string) $v) . '</td>';
        }
        echo '</tr>';
    }
    echo '</tbody></table>';
}
