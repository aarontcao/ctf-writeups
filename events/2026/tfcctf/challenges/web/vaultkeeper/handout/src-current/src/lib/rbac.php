<?php


function vk_scope_rank(string $scope): int {
    return ['guest' => 0, 'viewer' => 1, 'operator' => 2, 'maintainer' => 3, 'admin' => 4][$scope] ?? 0;
}

function vk_policy_allows(string $scope, string $action): bool {
    $need = [
        'jobs.read'      => 'guest',
        'bundle.upload'  => 'guest',
        'db.import'      => 'maintainer',
        'files.restore'  => 'operator',
        'schedule.write' => 'operator',
        'console.open'   => 'admin',
        'node.replicate' => 'admin',
    ][$action] ?? 'admin';
    return vk_scope_rank($scope) >= vk_scope_rank($need);
}
