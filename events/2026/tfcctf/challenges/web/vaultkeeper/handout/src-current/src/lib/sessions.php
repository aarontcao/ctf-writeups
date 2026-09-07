<?php



require_once __DIR__ . '/util.php';
require_once __DIR__ . '/accounts.php';

function vk_console_sessions(): array {
    $members = vk_members();
    $out = [];
    $agents = ['Firefox / macOS', 'Chrome / Windows', 'Safari / iOS', 'curl / CLI'];
    $i = 0;
    foreach ($members as $m) {
        if (($m['status'] ?? '') !== 'active') continue;
        $out[] = [
            'id'       => 'sess_' . substr(hash('sha1', $m['id'] . 'sess'), 0, 10),
            'member'   => $m['name'],
            'role'     => $m['role'],
            'ip'       => '10.0.' . (10 + $i) . '.' . (2 + $i),
            'agent'    => $agents[$i % count($agents)],
            'started'  => gmdate('c', time() - 3600 * ($i + 1)),
            'mfa'      => !empty($m['mfa']),
        ];
        $i++;
    }
    return $out;
}

function vk_session_get(string $id): ?array {
    foreach (vk_console_sessions() as $s) if (($s['id'] ?? '') === $id) return $s;
    return null;
}
