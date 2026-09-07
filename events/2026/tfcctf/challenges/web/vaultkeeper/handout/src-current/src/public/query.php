<?php

require_once __DIR__ . '/../lib/nav.php';
require_once __DIR__ . '/../lib/search.php';

vk_page_head('Query console', '/query.php');
?>
<section class="card">
  <p class="muted">Search the public backup catalog with a filter expression. Filters run
     read-only against the restore staging schema.</p>
  <form id="q">
    <input name="filter" placeholder="e.g. kind = 'backup' AND bytes &gt; 1000000000" style="width:32rem" value="kind = 'backup'">
    <button>Run</button>
  </form>
  <pre id="out" class="out" hidden></pre>
</section>
<section class="card">
  <h2>Saved searches</h2>
  <?php vk_table(vk_saved_searches(), ['id' => 'ID', 'name' => 'Name', 'filter' => 'Filter']); ?>
</section>
<script>
document.getElementById('q').addEventListener('submit', async e => {
  e.preventDefault();
  const u = new URLSearchParams({filter: e.target.filter.value});
  const r = await fetch('/api/query.php?' + u.toString());
  const o = document.getElementById('out'); o.hidden = false; o.textContent = JSON.stringify(await r.json(), null, 2);
});
</script>
<?php vk_page_foot();
