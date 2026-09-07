<?php

function db(): PDO {
    static $pdo = null;
    if ($pdo === null) {
        $host = getenv('DB_HOST') ?: '127.0.0.1';
        $name = getenv('DB_NAME') ?: 'vaultkeeper';
        $user = getenv('DB_USER') ?: 'vk_app';
        $pass = getenv('DB_PASS') ?: 'vk_app_pw';
        $pdo = new PDO("mysql:host=$host;dbname=$name;charset=utf8mb4", $user, $pass, [
            PDO::ATTR_ERRMODE            => PDO::ERRMODE_EXCEPTION,
            PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
            PDO::ATTR_EMULATE_PREPARES       => true,
            PDO::MYSQL_ATTR_MULTI_STATEMENTS => true,
        ]);
    }
    return $pdo;
}


function db_restore(): PDO {
    static $pdo = null;
    if ($pdo === null) {
        $host = getenv('DB_HOST') ?: '127.0.0.1';
        $user = getenv('DB_RESTORE_USER') ?: 'vk_restore';
        $pass = getenv('DB_RESTORE_PASS') ?: 'vk_restore_pw';
        $pdo = new PDO("mysql:host=$host;dbname=vk_restore;charset=utf8mb4", $user, $pass, [
            PDO::ATTR_ERRMODE                => PDO::ERRMODE_EXCEPTION,
            PDO::ATTR_DEFAULT_FETCH_MODE     => PDO::FETCH_ASSOC,
            PDO::ATTR_EMULATE_PREPARES       => true,
            PDO::MYSQL_ATTR_MULTI_STATEMENTS => true,
        ]);
        $pdo->exec("SET SESSION max_statement_time=15");
    }
    return $pdo;
}
