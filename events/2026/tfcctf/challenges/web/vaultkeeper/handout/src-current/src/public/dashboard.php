<?php

require_once __DIR__ . '/../lib/nav.php';
require_once __DIR__ . '/../lib/models.php';

$d = vk_dashboard();
vk_page_head('Overview', '/dashboard.php');
?>
<section class="card">
  <div class="stat-row">
    <div class="stat"><b><?=$d['schedules']?></b><span>schedules</span></div>
    <div class="stat"><b><?=$d['snapshots']?></b><span>snapshots</span></div>
    <div class="stat"><b><?=$d['connectors']?></b><span>destinations</span></div>
    <div class="stat"><b><?=vk_h($d['stored'])?></b><span>under management</span></div>
  </div>
  <p class="muted">Workspace <b><?=vk_h($d['workspace'])?></b> · node <code><?=vk_h($d['node'])?></code></p>
</section>
<section class="card">
  <h2>Jobs by status</h2>
  <?php
    $rows = [];
    foreach ($d['jobs_by_status'] as $s => $c) $rows[] = ['status' => $s, 'count' => $c];
    vk_table($rows, ['status' => 'Status', 'count' => 'Count']);
  ?>
</section>
<section class="card">
  <h2>Recent restore activity</h2>
  <?php vk_table(array_slice(vk_restore_history(8), 0, 8), ['ref' => 'Ref', 'kind' => 'Kind', 'source' => 'Source', 'status' => 'Status', 'queued' => 'Queued']); ?>
  <p class="muted"><a href="/history.php">Full restore history →</a></p>
</section>
<?php vk_page_foot();
