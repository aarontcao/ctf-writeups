CREATE DATABASE IF NOT EXISTS vaultkeeper CHARACTER SET utf8mb4;
CREATE DATABASE IF NOT EXISTS vk_restore  CHARACTER SET utf8mb4;

USE vk_restore;
CREATE TABLE catalog (
    id    INT AUTO_INCREMENT PRIMARY KEY,
    name  VARCHAR(128) NOT NULL,
    bytes BIGINT NOT NULL,
    kind  VARCHAR(16) NOT NULL DEFAULT 'backup'
);
INSERT INTO catalog (name, bytes, kind) VALUES
 ('nightly-full-2026-08-01', 5368709120, 'backup'),
 ('nightly-full-2026-08-08', 5478223360, 'backup'),
 ('staging-rollback-2026-08-12', 214748364, 'restore'),
 ('media-archive-q2', 32212254720, 'backup');

USE vaultkeeper;

CREATE TABLE jobs (
    id           INT AUTO_INCREMENT PRIMARY KEY,
    session_id   CHAR(24)     NOT NULL UNIQUE,
    kind         VARCHAR(16)  NOT NULL DEFAULT 'restore',
    source_label VARCHAR(128) NOT NULL DEFAULT '',
    status       VARCHAR(24)  NOT NULL DEFAULT 'queued',
    role         VARCHAR(16)  NOT NULL DEFAULT 'guest',
    bundle_path  VARCHAR(255) NULL,
    created_at   DECIMAL(20,6) NOT NULL,
    updated_at   DECIMAL(20,6) NOT NULL
);

INSERT INTO jobs (session_id, kind, source_label, status, role, created_at, updated_at) VALUES
 ('68ae1f0300071af000000000','backup','nightly / full',        'completed','operator', 1690001000.000000, 1690001200.000000),
 ('68ae2c9100033b4200000000','backup','nightly / incremental', 'completed','operator', 1690087400.000000, 1690087460.000000),
 ('68ae40120004aa1000000000','backup','staging rollback',      'completed','operator', 1690173810.000000, 1690173999.000000);

CREATE USER IF NOT EXISTS 'vk_app'@'%' IDENTIFIED BY 'vk_app_pw';
GRANT SELECT, INSERT, UPDATE, DELETE, CREATE, DROP, ALTER, INDEX, REFERENCES ON vaultkeeper.* TO 'vk_app'@'%';
GRANT SELECT, CREATE, DROP ON vk_restore.* TO 'vk_app'@'%';

CREATE USER IF NOT EXISTS 'vk_restore'@'%' IDENTIFIED BY 'vk_restore_pw';
GRANT SELECT, INSERT, UPDATE, DELETE, CREATE, DROP, ALTER, INDEX ON vk_restore.* TO 'vk_restore'@'%';

FLUSH PRIVILEGES;
