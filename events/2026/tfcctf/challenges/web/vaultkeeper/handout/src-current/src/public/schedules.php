<?php

require_once __DIR__ . '/../lib/nav.php';
require_once __DIR__ . '/../lib/models.php';

$rows = vk_schedules();
foreach ($rows as &$r) { $r['next_run'] = vk_next_run($r['cron'] ?? '0 * * * *'); }
unset($r);
vk_page_head('Backup schedules', '/schedules.php');
?>
<section class="card">
  <p class="muted">Snapshots run on a cron cadence and ship to a destination connector.
     Retention prunes older snapshots automatically.</p>
  <?php vk_table($rows, [
      'name' => 'Schedule', 'kind' => 'Kind', 'cron' => 'Cadence',
      'destination' => 'Destination', 'retention_days' => 'Keep (days)',
      'enabled' => 'Enabled', 'last_run' => 'Last run', 'next_run' => 'Next run']); ?>
</section>
<section class="card">
  <h2>New schedule</h2>
  <form id="f">
    <input name="name" placeholder="name (e.g. nightly / full)" required>
    <select name="kind"><option>full</option><option>incremental</option><option>archive</option></select>
    <input name="cron" placeholder="cron (0 2 * * *)" value="0 2 * * *">
    <input name="destination" placeholder="destination id" value="s3-primary">
    <input name="retention_days" type="number" value="30" style="width:6rem">
    <button>Add schedule</button>
  </form>
  <pre id="out" class="out" hidden></pre>
</section>
<script>
document.getElementById('f').addEventListener('submit', async e => {
  e.preventDefault();
  const b = Object.fromEntries(new FormData(e.target).entries());
  const r = await fetch('/api/schedules.php', {method:'POST', headers:{'Content-Type':'application/json'}, body: JSON.stringify(b)});
  const o = document.getElementById('out'); o.hidden = false; o.textContent = JSON.stringify(await r.json(), null, 2);
  setTimeout(() => location.reload(), 600);
});
</script>
<?php vk_page_foot();
