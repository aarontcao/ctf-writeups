<?php

require_once __DIR__ . '/../lib/nav.php';
require_once __DIR__ . '/../lib/models.php';
vk_page_head('API tokens', '/apitokens.php');
?>
<section class="card">
  <p class="muted">Programmatic access tokens for the appliance API. New tokens are
     capped at <code>viewer</code> scope unless minted by an admin token.
     The secret is shown once at creation and never stored in clear.</p>
  <?php vk_table(vk_apitokens(), ['id' => 'ID', 'name' => 'Name', 'scope' => 'Scope', 'created' => 'Created', 'revoked' => 'Revoked', 'last_used' => 'Last used']); ?>
</section>
<section class="card">
  <h2>Issue token</h2>
  <form id="f">
    <input name="name" placeholder="label" required>
    <select name="scope"><option>viewer</option><option>operator</option><option>maintainer</option><option>admin</option></select>
    <button>Issue</button>
  </form>
  <pre id="out" class="out" hidden></pre>
</section>
<script>
document.getElementById('f').addEventListener('submit', async e => {
  e.preventDefault();
  const b = Object.fromEntries(new FormData(e.target).entries());
  const r = await fetch('/api/apitokens.php', {method:'POST', headers:{'Content-Type':'application/json'}, body: JSON.stringify(b)});
  const o = document.getElementById('out'); o.hidden = false; o.textContent = JSON.stringify(await r.json(), null, 2);
  setTimeout(() => location.reload(), 1500);
});
</script>
<?php vk_page_foot();
