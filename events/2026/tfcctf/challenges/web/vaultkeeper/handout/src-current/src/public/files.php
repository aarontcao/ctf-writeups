<?php

require_once __DIR__ . '/../lib/nav.php';
require_once __DIR__ . '/../lib/snapstore.php';

$path = (string) ($_GET['path'] ?? '');
$list = vk_snap_list($path);
vk_page_head('Snapshot files', '/files.php');
?>
<section class="card">
  <p class="muted">Read-only view of the file tree extracted from imported snapshots, under the
     restore staging area.</p>
  <p class="muted">Path: <code>/<?=vk_h($list['path'] ?? '')?></code></p>
  <?php if (isset($list['error'])): ?>
    <p class="err"><?=vk_h($list['error'])?></p>
  <?php else: ?>
    <table class="jobs"><thead><tr><th>Name</th><th>Type</th><th>Size</th></tr></thead><tbody>
      <?php foreach ($list['entries'] as $e): ?>
        <tr>
          <td>
            <?php $child = ltrim(($list['path'] ? $list['path'] . '/' : '') . $e['name'], '/'); ?>
            <?php if ($e['type'] === 'dir'): ?>
              <a href="/files.php?path=<?=rawurlencode($child)?>"><?=vk_h($e['name'])?>/</a>
            <?php else: ?>
              <a href="/api/snapshot_file.php?read=1&path=<?=rawurlencode($child)?>"><?=vk_h($e['name'])?></a>
            <?php endif; ?>
          </td>
          <td><?=vk_h($e['type'])?></td>
          <td><?=number_format((int)$e['bytes'])?> B</td>
        </tr>
      <?php endforeach; ?>
      <?php if (!$list['entries']): ?><tr><td colspan="3" class="muted">Empty.</td></tr><?php endif; ?>
    </tbody></table>
  <?php endif; ?>
</section>
<?php vk_page_foot();
