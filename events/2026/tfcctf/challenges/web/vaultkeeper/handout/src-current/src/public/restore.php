<?php

require_once __DIR__ . '/../lib/db.php';
require_once __DIR__ . '/../lib/util.php';
require_once __DIR__ . '/../lib/archive.php';
require_once __DIR__ . '/../lib/restore_state.php';
require_once __DIR__ . '/../lib/recovery.php';
require_once __DIR__ . '/../lib/journal.php';
require_once __DIR__ . '/../lib/spool.php';
require_once __DIR__ . '/../engine/restore_engine.php';

function load_job(string $sid): ?array {
    $st = db()->prepare("SELECT * FROM jobs WHERE session_id = ? AND kind = 'restore'");
    $st->execute([$sid]);
    return $st->fetch() ?: null;
}

$sid = (string)($_GET['job'] ?? '');
$job = $sid !== '' ? load_job($sid) : null;

if (!$job) {
    http_response_code(403);
    header('Content-Type: text/html');
    echo '<!doctype html><meta charset=utf-8><title>Restore console</title>';
    echo '<body style="font-family:system-ui;background:#0d1117;color:#c9d1d9;padding:3rem">';
    echo '<h2>Restore session not found</h2><p>This restore link is invalid or has expired.</p>';
    exit;
}

$notice = '';
$bundle_dir = VK_DATA . '/bundles';
@mkdir($bundle_dir, 0755, true);
$bundle_path = $bundle_dir . '/' . $job['id'] . '.vkb';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $action = $_POST['action'] ?? '';

    if ($action === 'upload_bundle' && !empty($_FILES['bundle']['tmp_name'])) {
        move_uploaded_file($_FILES['bundle']['tmp_name'], $bundle_path);
        db()->prepare("UPDATE jobs SET bundle_path=?, status='bundle-received', updated_at=? WHERE id=?")
            ->execute([$bundle_path, vk_now(), $job['id']]);
        $notice = 'Bundle uploaded (' . number_format(filesize($bundle_path)) . ' bytes). Ready to import.';
    }

    elseif ($action === 'import_db') {
        if (!is_file($bundle_path)) { $notice = 'Upload a bundle first.'; }
        else {
            $entries = vk_tar_parse(file_get_contents($bundle_path));
            $sql     = vk_tar_get($entries, 'database.sql');
            $cap     = $_POST['cap'] ?? '';
            $scope   = vk_cap_scope($cap);
            if (!in_array($scope, ['maintainer', 'operator'], true)) {
                $notice = 'Import requires a maintainer capability (current scope: ' . vk_h((string) ($scope ?? 'none')) . ').';
            } elseif ($sql === null) { $notice = 'Bundle contains no database.sql manifest.'; }
            else {
                try {
                    $res = vk_import_database($sql);
                    db()->prepare("UPDATE jobs SET status='db-imported', updated_at=? WHERE id=?")
                        ->execute([vk_now(), $job['id']]);
                    $notice = 'Database manifest imported. Staging tables reconciled: '
                            . vk_h(implode(', ', $res['dropped']) ?: '(none)');
                } catch (Throwable $e) {
                    $notice = 'Import error: ' . vk_h($e->getMessage());
                }
            }
        }
    }

    elseif ($action === 'system_restore') {
        
        $job = load_job($sid);
        if (($job['role'] ?? 'guest') !== 'operator') {
            $notice = 'System file restore requires an operator-scoped restore session.';
        } elseif (!is_file($bundle_path)) {
            $notice = 'Upload a bundle first.';
        } else {
            $entries = vk_tar_parse(file_get_contents($bundle_path));
            $written = vk_restore_files($entries, (int)$job['id']);
            
            $checkpoint = vk_tar_get($entries, 'state.dat');
            if ($checkpoint !== null) {
                $resumed = vk_resume_checkpoint($checkpoint);
            }
            db()->prepare("UPDATE jobs SET status='files-restored', updated_at=? WHERE id=?")
                ->execute([vk_now(), $job['id']]);
            $notice = 'File tree restored (' . count($written) . ' objects); checkpoint resumed.';
        }
    }

    $job = load_job($sid); 
}

$role = $job['role'];
?>
<!doctype html><html><head><meta charset="utf-8">
<title>Vaultkeeper · Restore console</title>
<link rel="stylesheet" href="/assets/style.css">
</head><body>
<div class="wrap">
  <header class="bar"><span class="logo">▤ Vaultkeeper</span><span class="tag">restore console</span></header>

  <section class="card">
    <h1>Restore session <code><?=vk_h($job['session_id'])?></code></h1>
    <table class="kv">
      <tr><td>Job</td><td>#<?=$job['id']?></td></tr>
      <tr><td>Source</td><td><?=vk_h($job['source_label'])?></td></tr>
      <tr><td>Status</td><td><span class="pill"><?=vk_h($job['status'])?></span></td></tr>
      <tr><td>Scope</td><td><span class="pill <?=$role==='operator'?'op':''?>"><?=vk_h($role)?></span></td></tr>
    </table>
  </section>

  <?php if ($notice): ?><div class="notice"><?=$notice?></div><?php endif; ?>

  <section class="card">
    <h2>1 · Upload backup bundle</h2>
    <p class="muted">Accepted format: Vaultkeeper bundle (<code>.vkb</code>) — an uncompressed archive
       containing <code>database.sql</code> and the site file tree.</p>
    <form method="post" enctype="multipart/form-data">
      <input type="hidden" name="action" value="upload_bundle">
      <input type="file" name="bundle" required>
      <button>Upload bundle</button>
    </form>
  </section>

  <section class="card">
    <h2>2 · Import database manifest</h2>
    <p class="muted">Replays <code>database.sql</code> into the restore schema and reconciles staging tables.</p>
    <form method="post"><input type="hidden" name="action" value="import_db"><button>Import database</button></form>
  </section>

  <section class="card">
    <h2>3 · Restore file tree <span class="op-only">operator</span></h2>
    <p class="muted">Extracts the bundle's file entries onto the appliance. Requires operator scope.</p>
    <form method="post"><input type="hidden" name="action" value="system_restore"><button>Run system restore</button></form>
  </section>
</div>
</body></html>
