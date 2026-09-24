<?php

require_once __DIR__ . '/../lib/nav.php';
require_once __DIR__ . '/../lib/store.php';

$ref  = preg_replace('/[^a-f0-9]/', '', strtolower((string) ($_GET['ref'] ?? '')));
$rows = array_values(array_filter(vk_store_load('annotations', []), fn($r) => ($r['ref'] ?? '') === $ref));

vk_page_head('Run annotations', '/history.php');
?>
<section class="card">
  <p class="muted">Operator notes attached to restore run
     <code><?=vk_h($ref !== '' ? $ref : '—')?></code>.</p>
  <?php if (!$rows): ?>
    <p class="muted">No annotations for this run yet.</p>
  <?php else: foreach ($rows as $r): ?>
    <div class="notice" style="margin:.4rem 0">
      <b><?=vk_h($r['author'] ?? 'operator')?></b>
      <span class="muted"><?=vk_h($r['ts'] ?? '')?></span>
      <div class="note-body"><?=$r['note'] ?? ''?></div>
    </div>
  <?php endforeach; endif; ?>
</section>
<section class="card">
  <h2>Add annotation</h2>
  <form id="f">
    <input type="hidden" name="ref" value="<?=vk_h($ref)?>">
    <input name="author" placeholder="your name" value="operator">
    <input name="note" placeholder="note" required>
    <button>Save note</button>
  </form>
  <pre id="out" class="out" hidden></pre>
</section>
<script>
document.getElementById('f').addEventListener('submit', async e => {
  e.preventDefault();
  const b = Object.fromEntries(new FormData(e.target).entries());
  const r = await fetch('/api/annotations.php', {method:'POST', headers:{'Content-Type':'application/json'}, body: JSON.stringify(b)});
  const o = document.getElementById('out'); o.hidden = false; o.textContent = JSON.stringify(await r.json(), null, 2);
  setTimeout(() => location.reload(), 600);
});
</script>
<?php vk_page_foot();
