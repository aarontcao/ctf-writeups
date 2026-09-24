<?php

require_once __DIR__ . '/../lib/nav.php';
require_once __DIR__ . '/../lib/models.php';
require_once __DIR__ . '/../lib/logger.php';

$limit = max(1, min(100, (int) ($_GET['limit'] ?? 25)));
vk_page_head('Restore history', '/history.php');
?>
<section class="card">
  <p class="muted">Every queued backup and restore job, newest first.
     Open a run's <a href="/annotations.php">annotations</a> by its ref to review operator notes.</p>
  <?php vk_table(vk_restore_history($limit), [
      'id' => '#', 'ref' => 'Ref', 'kind' => 'Kind', 'source' => 'Source',
      'status' => 'Status', 'scope' => 'Scope', 'queued' => 'Queued', 'duration' => 'Duration']); ?>
</section>
<section class="card">
  <h2>Appliance audit trail</h2>
  <pre class="out"><?php
    foreach (vk_audit_tail(30) as $line) echo vk_h($line) . "\n";
  ?></pre>
</section>
<?php vk_page_foot();
