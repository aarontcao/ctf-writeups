<?php

require_once __DIR__ . '/../lib/nav.php';
require_once __DIR__ . '/../lib/quota.php';

$o = vk_quota_overview();
$f = vk_quota_forecast(30);
vk_page_head('Capacity', '/capacity.php');
?>
<section class="card">
  <div class="stat-row">
    <div class="stat"><b><?=vk_h($o['used'])?></b><span>used</span></div>
    <div class="stat"><b><?=vk_h($o['limit'])?></b><span>quota</span></div>
    <div class="stat"><b><?=vk_h($o['percent'])?>%</b><span>utilised</span></div>
    <div class="stat"><b><?=vk_h($o['headroom'])?></b><span>headroom</span></div>
  </div>
  <p class="muted">Projected in <?=$f['horizon_days']?> days: <b><?=vk_h($f['projected'])?></b>
     (≈ <?=vk_h($f['daily_growth'])?>/day).</p>
</section>
<section class="card">
  <h2>By destination</h2>
  <?php vk_table(vk_quota_by_destination(), [
      'destination' => 'Destination', 'type' => 'Type', 'stored' => 'Stored', 'objects' => 'Objects', 'status' => 'Status']); ?>
</section>
<?php vk_page_foot();
