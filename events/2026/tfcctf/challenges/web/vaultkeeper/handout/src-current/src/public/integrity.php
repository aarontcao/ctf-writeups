<?php

require_once __DIR__ . '/../lib/nav.php';
vk_page_head('Bundle integrity', '/integrity.php');
?>
<section class="card">
  <p class="muted">Upload a <code>.vkb</code> bundle to inspect its structure before importing.
     The report lists entries and confirms the <code>database.sql</code> manifest — it does not
     extract or replay anything.</p>
  <form id="f" enctype="multipart/form-data">
    <input type="file" name="bundle" required>
    <label class="muted"><input type="checkbox" id="digests"> per-entry digests</label>
    <button>Inspect</button>
  </form>
  <pre id="out" class="out" hidden></pre>
</section>
<script>
document.getElementById('f').addEventListener('submit', async e => {
  e.preventDefault();
  const ep = document.getElementById('digests').checked ? '/api/verify_checksum.php' : '/api/integrity.php';
  const r = await fetch(ep, {method:'POST', body: new FormData(e.target)});
  const o = document.getElementById('out'); o.hidden = false; o.textContent = JSON.stringify(await r.json(), null, 2);
});
</script>
<?php vk_page_foot();
