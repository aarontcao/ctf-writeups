<?php

require_once __DIR__ . '/../lib/nav.php';
require_once __DIR__ . '/../lib/models.php';

$s = vk_settings();
vk_page_head('Workspace settings', '/settings.php');
?>
<section class="card">
  <form id="f">
    <label class="muted">Workspace name<br><input name="workspace" value="<?=vk_h($s['workspace'])?>"></label><br>
    <label class="muted">Timezone<br><input name="timezone" value="<?=vk_h($s['timezone'])?>"></label><br>
    <label class="muted">Default retention (days)<br><input name="retention_days" type="number" value="<?=vk_h((string)$s['retention_days'])?>"></label><br>
    <label class="muted">Max bundle (MB)<br><input name="max_bundle_mb" type="number" value="<?=vk_h((string)$s['max_bundle_mb'])?>"></label><br>
    <label class="muted">Default destination<br><input name="default_dest" value="<?=vk_h($s['default_dest'])?>"></label><br>
    <label class="muted">Compression<br>
      <select name="compression">
        <?php foreach (['zstd','gzip','none'] as $o): ?>
          <option <?=$s['compression']===$o?'selected':''?>><?=$o?></option>
        <?php endforeach; ?>
      </select></label><br>
    <button>Save settings</button>
  </form>
  <pre id="out" class="out" hidden></pre>
</section>
<script>
document.getElementById('f').addEventListener('submit', async e => {
  e.preventDefault();
  const b = Object.fromEntries(new FormData(e.target).entries());
  const r = await fetch('/api/settings.php', {method:'POST', headers:{'Content-Type':'application/json'}, body: JSON.stringify(b)});
  const o = document.getElementById('out'); o.hidden = false; o.textContent = JSON.stringify(await r.json(), null, 2);
});
</script>
<?php vk_page_foot();
