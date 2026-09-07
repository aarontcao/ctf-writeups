<?php

require_once __DIR__ . '/db.php';

function vk_table_columns(string $schema, string $table): array {
    $st = db()->prepare(
        "SELECT column_name, data_type FROM information_schema.columns
         WHERE table_schema = ? AND table_name = ? ORDER BY ordinal_position"
    );
    $st->execute([$schema, $table]);
    return $st->fetchAll();
}

function vk_live_table_set(): array {
    return db()->query(
        "SELECT table_name FROM information_schema.tables
         WHERE table_schema = 'vaultkeeper' AND table_type = 'BASE TABLE'"
    )->fetchAll(PDO::FETCH_COLUMN);
}
