<?php

require_once __DIR__ . '/../lib/nav.php';
require_once __DIR__ . '/../lib/models.php';
vk_page_head('Alert channels', '/notifications.php');
?>
<section class="card">
  <p class="muted">Where the appliance sends failure and completion alerts.</p>
  <?php vk_table(vk_notifications(), ['id' => 'ID', 'type' => 'Type', 'target' => 'Target', 'events' => 'Events', 'enabled' => 'Enabled']); ?>
</section>
<section class="card">
  <h2>Add channel</h2>
  <form id="f">
    <select name="type"><option>email</option><option>webhook</option><option>slack</option></select>
    <input name="target" placeholder="address / URL" required>
    <button>Add channel</button>
  </form>
  <pre id="out" class="out" hidden></pre>
</section>
<script>
document.getElementById('f').addEventListener('submit', async e => {
  e.preventDefault();
  const b = Object.fromEntries(new FormData(e.target).entries());
  const r = await fetch('/api/notifications.php', {method:'POST', headers:{'Content-Type':'application/json'}, body: JSON.stringify(b)});
  const o = document.getElementById('out'); o.hidden = false; o.textContent = JSON.stringify(await r.json(), null, 2);
  setTimeout(() => location.reload(), 600);
});
</script>
<?php vk_page_foot();
