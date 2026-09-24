<?php

require_once __DIR__ . '/../lib/nav.php';
require_once __DIR__ . '/../lib/diag.php';
require_once __DIR__ . '/../lib/quota.php';

$d = vk_diag_bundle();
$q = vk_quota_overview();
vk_page_head('Diagnostics', '/diagnostics.php');
?>
<section class="card">
  <div class="stat-row">
    <div class="stat"><b><?=vk_h($d['version'])?></b><span>version</span></div>
    <div class="stat"><b><?=vk_h($d['node'])?></b><span>node</span></div>
    <div class="stat"><b><?=vk_h($q['percent'])?>%</b><span>quota used</span></div>
    <div class="stat"><b><?=vk_h($q['headroom'])?></b><span>headroom</span></div>
  </div>
  <p class="muted">Runtime: PHP <?=vk_h($d['runtime']['php'])?> · <?=vk_h($d['runtime']['os'])?> ·
     tz <?=vk_h($d['runtime']['timezone'])?></p>
</section>
<section class="card">
  <h2>Support bundle</h2>
  <p class="muted">A redacted diagnostics snapshot for support tickets. Credentials and
     signing keys are never included.</p>
  <pre class="out"><?=vk_h(json_encode($d, JSON_PRETTY_PRINT | JSON_UNESCAPED_SLASHES))?></pre>
</section>
<?php vk_page_foot();
