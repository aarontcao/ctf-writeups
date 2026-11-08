<?php require_once __DIR__ . '/../lib/util.php'; ?>
<!doctype html><html><head><meta charset="utf-8">
<title>Vaultkeeper — Backup & Restore Appliance</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" href="/assets/style.css">
</head><body>
<div class="wrap">
  <header class="bar"><span class="logo">▤ Vaultkeeper</span><span class="tag">appliance 4.2.1</span></header>
  <nav class="subnav" style="display:flex;gap:.4rem;flex-wrap:wrap;margin:.4rem 0 1rem">
    <a class="pill" href="/dashboard.php">Overview</a>
    <a class="pill" href="/schedules.php">Schedules</a>
    <a class="pill" href="/snapshots.php">Snapshots</a>
    <a class="pill" href="/files.php">Files</a>
    <a class="pill" href="/connectors.php">Destinations</a>
    <a class="pill" href="/policies.php">Retention</a>
    <a class="pill" href="/history.php">Restore history</a>
    <a class="pill" href="/query.php">Query</a>
    <a class="pill" href="/capacity.php">Capacity</a>
    <a class="pill" href="/notifications.php">Alerts</a>
    <a class="pill" href="/webhooks.php">Webhooks</a>
    <a class="pill" href="/apitokens.php">API tokens</a>
    <a class="pill" href="/accounts.php">Access control</a>
    <a class="pill" href="/integrity.php">Integrity</a>
    <a class="pill" href="/replication.php">Replication</a>
    <a class="pill" href="/nodes.php">Cluster</a>
    <a class="pill" href="/exports.php">Exports</a>
    <a class="pill" href="/diagnostics.php">Diagnostics</a>
    <a class="pill" href="/settings.php">Settings</a>
  </nav>

  <section class="hero">
    <h1>Set-and-forget backups for your whole stack.</h1>
    <p>Vaultkeeper snapshots your databases and file trees on a schedule, ships them to any
       destination, and restores an entire site in minutes — no agents, no downtime.</p>
    <div class="stat-row">
      <div class="stat"><b>3</b><span>protected sites</span></div>
      <div class="stat"><b>128 GiB</b><span>under management</span></div>
      <div class="stat"><b>99.98%</b><span>restore success</span></div>
    </div>
  </section>

  <section class="card">
    <h2>Restore queue</h2>
    <p class="muted">Live status of your backup and restore jobs.</p>
    <table class="jobs" id="jobs"><thead>
      <tr><th>#</th><th>Kind</th><th>Source</th><th>Status</th><th>Queued</th></tr>
    </thead><tbody><tr><td colspan="5" class="muted">loading…</td></tr></tbody></table>
  </section>

  <section class="card">
    <h2>Need to roll back?</h2>
    <p class="muted">Request a self-service restore. Once queued, the account owner receives a
       one-time restore-session link to upload the recovery bundle.</p>
    <form id="req">
      <input name="source_label" placeholder="what are you restoring? (e.g. staging rollback)" required>
      <button>Request restore</button>
    </form>
    <pre id="reqout" class="out" hidden></pre>
  </section>

  <?php
    $sample_secret = getenv('VK_SAMPLE_SECRET') ?: 'sample-signing-secret-v3';
    $sample_name   = 'demo-nightly.vkb';
    $sample_sig    = md5($sample_secret . $sample_name);
  ?>
  <section class="card">
    <h2>Resources</h2>
    <p class="muted">Download a sample bundle to explore the format:
      <a href="/api/download_sample.php?name=<?=$sample_name?>&amp;sig=<?=$sample_sig?>">demo-nightly.vkb</a>
      · <a href="/view.php?doc=api">Documentation</a></p>
  </section>

  <footer class="foot">© 2026 Vaultkeeper · Backup &amp; Restore Appliance 4.2.1</footer>
</div>
<script>
async function loadJobs(){
  try{
    const r = await fetch('/api/jobs.php'); const j = await r.json();
    const tb = document.querySelector('#jobs tbody'); tb.innerHTML='';
    for(const it of j.queue){
      const tr=document.createElement('tr');
      tr.innerHTML=`<td>${it.id}</td><td>${it.kind}</td><td>${it.source}</td>`+
                   `<td><span class="pill">${it.status}</span></td><td>${it.queued_at}</td>`;
      tb.appendChild(tr);
    }
  }catch(e){}
}
document.querySelector('#req').addEventListener('submit', async e=>{
  e.preventDefault();
  const body = JSON.stringify({source_label: e.target.source_label.value});
  const r = await fetch('/api/request_restore.php',{method:'POST',headers:{'Content-Type':'application/json'},body});
  const out = document.querySelector('#reqout');
  out.hidden=false; out.textContent = JSON.stringify(await r.json(), null, 2);
  loadJobs();
});
loadJobs(); setInterval(loadJobs, 4000);
</script>
</body></html>
