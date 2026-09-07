<?php

require_once __DIR__ . '/../lib/nav.php';
require_once __DIR__ . '/../lib/cluster.php';
$s = vk_cluster_summary();
vk_page_head('Cluster & replication', '/nodes.php');
?>
<section class="card">
  <div class="stat-row">
    <div class="stat"><b><?=$s['nodes']?></b><span>nodes</span></div>
    <div class="stat"><b><?=$s['healthy']?></b><span>healthy</span></div>
    <div class="stat"><b><?=$s['quorum']?'yes':'no'?></b><span>quorum</span></div>
  </div>
  <?php vk_table(vk_cluster_nodes(), ['node' => 'Node', 'role' => 'Role', 'state' => 'State', 'lag_ms' => 'Replica lag (ms)', 'jobs' => 'Jobs']); ?>
</section>
<?php vk_page_foot();
