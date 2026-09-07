<?php

require_once __DIR__ . '/../lib/nav.php';
require_once __DIR__ . '/../lib/policies.php';
require_once __DIR__ . '/../engine/gc_engine.php';

$policies = vk_policies();
vk_page_head('Retention policies', '/policies.php');
?>
<section class="card">
  <p class="muted">Retention policies pin how long a class of snapshots is kept. Locked
     policies (legal holds) cannot be shortened or removed through the console.</p>
  <?php
    $rows = array_map(function ($p) {
        $p['keep_count'] = $p['keep_count'] ?? '—';
        $p['locked'] = !empty($p['locked']) ? 'yes' : 'no';
        $p['holds'] = count($p['holds'] ?? []) . ' snapshot(s)';
        return $p;
    }, $policies);
    vk_table($rows, ['name' => 'Policy', 'keep_days' => 'Keep (days)', 'keep_count' => 'Keep (count)', 'scope' => 'Scope', 'locked' => 'Locked', 'holds' => 'Holds']);
  ?>
</section>
<section class="card">
  <h2>GC dry run</h2>
  <?php $plan = vk_gc_plan((int) ($policies[0]['keep_days'] ?? 30), $policies[0]['keep_count'] ?? null, $policies[0]['holds'] ?? []); ?>
  <p class="muted">Under <b><?=vk_h($policies[0]['name'] ?? 'Default')?></b>:
     keep <b><?=$plan['kept']?></b>, hold <b><?=$plan['held']?></b>, prune
     <b><?=$plan['pruned']?></b> — reclaim <b><?=vk_h($plan['reclaim'])?></b>.</p>
</section>
<section class="card">
  <h2>New policy</h2>
  <form id="f">
    <input name="name" placeholder="name" required>
    <input name="keep_days" type="number" value="30" style="width:7rem" placeholder="keep days">
    <input name="keep_count" type="number" style="width:7rem" placeholder="keep count">
    <input name="scope" placeholder="scope (all / finance / staging)" value="all">
    <button>Add policy</button>
  </form>
  <pre id="out" class="out" hidden></pre>
</section>
<script>
document.getElementById('f').addEventListener('submit', async e => {
  e.preventDefault();
  const b = Object.fromEntries(new FormData(e.target).entries());
  const r = await fetch('/api/policies.php', {method:'POST', headers:{'Content-Type':'application/json'}, body: JSON.stringify(b)});
  const o = document.getElementById('out'); o.hidden = false; o.textContent = JSON.stringify(await r.json(), null, 2);
  setTimeout(() => location.reload(), 800);
});
</script>
<?php vk_page_foot();
