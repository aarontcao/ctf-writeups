<?php

require_once __DIR__ . '/../lib/nav.php';
require_once __DIR__ . '/../lib/alerts.php';

$eval = vk_alert_evaluate();
vk_page_head('Alert rules', '/alerts.php');
?>
<section class="card">
  <p class="muted">Rules watch engine metrics and fire when a threshold is crossed. Firing
     rules deliver to the configured <a href="/notifications.php">alert channels</a> and
     <a href="/webhooks.php">webhooks</a>.</p>
  <?php
    $rows = array_map(function ($e) {
        $e['firing'] = $e['firing'] ? 'FIRING' : 'ok';
        return $e;
    }, $eval);
    vk_table($rows, ['rule' => 'Rule', 'metric' => 'Metric', 'value' => 'Current', 'threshold' => 'Threshold', 'severity' => 'Severity', 'firing' => 'State']);
  ?>
</section>
<section class="card">
  <h2>New rule</h2>
  <form id="f">
    <input name="name" placeholder="name" required>
    <select name="metric"><option>jobs_failed</option><option>replica_lag_ms</option><option>quota_percent</option></select>
    <select name="op"><option>gt</option><option>lt</option><option>eq</option></select>
    <input name="threshold" type="number" value="0" style="width:7rem">
    <select name="severity"><option>warning</option><option>critical</option><option>info</option></select>
    <button>Add rule</button>
  </form>
  <pre id="out" class="out" hidden></pre>
</section>
<script>
document.getElementById('f').addEventListener('submit', async e => {
  e.preventDefault();
  const b = Object.fromEntries(new FormData(e.target).entries());
  const r = await fetch('/api/alertrules.php', {method:'POST', headers:{'Content-Type':'application/json'}, body: JSON.stringify(b)});
  const o = document.getElementById('out'); o.hidden = false; o.textContent = JSON.stringify(await r.json(), null, 2);
  setTimeout(() => location.reload(), 800);
});
</script>
<?php vk_page_foot();
