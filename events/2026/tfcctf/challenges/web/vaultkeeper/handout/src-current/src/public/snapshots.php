<?php

require_once __DIR__ . '/../lib/nav.php';
require_once __DIR__ . '/../lib/models.php';

$snaps = vk_snapshots();
$diff  = null;
if (isset($_GET['a'], $_GET['b'])) $diff = vk_snapshot_diff((int) $_GET['a'], (int) $_GET['b']);
vk_page_head('Snapshot catalog', '/snapshots.php');
?>
<section class="card">
  <?php vk_table($snaps, ['id' => '#', 'name' => 'Snapshot', 'kind' => 'Kind', 'size' => 'Size', 'blocks' => 'Blocks', 'sha' => 'Digest']); ?>
  <p class="muted">Labels &amp; cost tags are available per snapshot via
     <a href="/api/tags.php">/api/tags.php</a>.</p>
</section>
<section class="card">
  <h2>Compare two snapshots</h2>
  <form method="get">
    <input name="a" type="number" placeholder="from #" style="width:6rem" required>
    <input name="b" type="number" placeholder="to #" style="width:6rem" required>
    <button>Diff</button>
  </form>
  <?php if ($diff): ?>
    <?php if (isset($diff['error'])): ?>
      <p class="err"><?=vk_h($diff['error'])?></p>
    <?php else: ?>
      <p class="muted"><b><?=vk_h($diff['from'])?></b> (<?=vk_h($diff['from_size'])?>)
         → <b><?=vk_h($diff['to'])?></b> (<?=vk_h($diff['to_size'])?>):
         <?=vk_h($diff['direction'])?> by <?=vk_h($diff['delta'])?>
         (<?=vk_h((string)$diff['block_delta'])?> blocks).</p>
    <?php endif; ?>
  <?php endif; ?>
</section>
<?php vk_page_foot();
