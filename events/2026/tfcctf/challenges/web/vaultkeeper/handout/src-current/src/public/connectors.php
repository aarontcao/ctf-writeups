<?php

require_once __DIR__ . '/../lib/nav.php';
require_once __DIR__ . '/../lib/models.php';
vk_page_head('Destination connectors', '/connectors.php');
?>
<section class="card">
  <p class="muted">Where snapshots are shipped. Credentials are stored server-side and never rendered.</p>
  <?php vk_table(vk_connectors(), [
      'id' => 'ID', 'type' => 'Type', 'name' => 'Name', 'region' => 'Region',
      'bucket' => 'Bucket / host', 'status' => 'Status', 'encrypted' => 'Encrypted']); ?>
</section>
<section class="card">
  <h2>Add connector</h2>
  <form id="f">
    <input name="name" placeholder="name" required>
    <select name="type"><option>s3</option><option>gcs</option><option>sftp</option><option>local</option></select>
    <input name="region" placeholder="region (s3/gcs)">
    <input name="bucket" placeholder="bucket / host">
    <button>Add destination</button>
  </form>
  <pre id="out" class="out" hidden></pre>
</section>
<script>
document.getElementById('f').addEventListener('submit', async e => {
  e.preventDefault();
  const b = Object.fromEntries(new FormData(e.target).entries());
  const r = await fetch('/api/connectors.php', {method:'POST', headers:{'Content-Type':'application/json'}, body: JSON.stringify(b)});
  const o = document.getElementById('out'); o.hidden = false; o.textContent = JSON.stringify(await r.json(), null, 2);
  setTimeout(() => location.reload(), 600);
});
</script>
<?php vk_page_foot();
