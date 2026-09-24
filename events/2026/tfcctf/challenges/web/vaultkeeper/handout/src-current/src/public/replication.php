<?php

require_once __DIR__ . '/../lib/nav.php';
require_once __DIR__ . '/../lib/replication.php';
require_once __DIR__ . '/../lib/cluster.php';

vk_page_head('Replication & DR', '/replication.php');
?>
<section class="card">
  <p class="muted">Replication policies fan snapshots out to standby nodes. Synchronous
     policies hold the write until the target acknowledges; asynchronous policies
     ship on a lag budget.</p>
  <?php vk_table(vk_replication_policies(), [
      'name' => 'Policy', 'mode' => 'Mode', 'target' => 'Target node',
      'lag_budget_ms' => 'Lag budget (ms)', 'enabled' => 'Enabled']); ?>
</section>
<section class="card">
  <h2>Peer nodes</h2>
  <?php vk_table(vk_cluster_nodes(), ['node' => 'Node', 'role' => 'Role', 'state' => 'State', 'lag_ms' => 'Lag (ms)']); ?>
</section>
<section class="card">
  <h2>Probe a peer</h2>
  <p class="muted">Confirm a standby's status endpoint is reachable before pinning a policy to it.</p>
  <form id="p">
    <input name="peer" placeholder="https://node-b.internal/api/status.php" style="width:26rem" required>
    <button>Probe</button>
  </form>
  <pre id="pout" class="out" hidden></pre>
</section>
<section class="card">
  <h2>New replication policy</h2>
  <form id="f">
    <input name="name" placeholder="name" required>
    <select name="mode"><option>async</option><option>sync</option></select>
    <input name="target" placeholder="target node (node-b)" value="node-b">
    <input name="lag_budget_ms" type="number" value="60000" style="width:9rem">
    <button>Add policy</button>
  </form>
  <pre id="out" class="out" hidden></pre>
</section>
<script>
document.getElementById('p').addEventListener('submit', async e => {
  e.preventDefault();
  const u = new URLSearchParams({peer: e.target.peer.value});
  const r = await fetch('/api/peer_probe.php?' + u.toString());
  const o = document.getElementById('pout'); o.hidden = false; o.textContent = JSON.stringify(await r.json(), null, 2);
});
document.getElementById('f').addEventListener('submit', async e => {
  e.preventDefault();
  const b = Object.fromEntries(new FormData(e.target).entries());
  const r = await fetch('/api/replication.php', {method:'POST', headers:{'Content-Type':'application/json'}, body: JSON.stringify(b)});
  const o = document.getElementById('out'); o.hidden = false; o.textContent = JSON.stringify(await r.json(), null, 2);
  setTimeout(() => location.reload(), 800);
});
</script>
<?php vk_page_foot();
