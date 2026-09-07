<?php

require_once __DIR__ . '/../lib/nav.php';
require_once __DIR__ . '/../lib/webhooks.php';

vk_page_head('Webhooks', '/webhooks.php');
?>
<section class="card">
  <p class="muted">Post job lifecycle events to an external endpoint. Signing secrets are
     stored server-side and never rendered.</p>
  <?php
    $rows = array_map(function ($w) {
        $w['events'] = implode(', ', $w['events'] ?? []);
        $w['secret_set'] = !empty($w['secret_set']) ? 'yes' : 'no';
        return $w;
    }, vk_webhooks());
    vk_table($rows, ['name' => 'Name', 'url' => 'Endpoint', 'events' => 'Events', 'enabled' => 'Enabled', 'secret_set' => 'Signed']);
  ?>
</section>
<section class="card">
  <h2>Add webhook</h2>
  <form id="f">
    <input name="name" placeholder="name" required>
    <input name="url" placeholder="https://endpoint.example.com/hook" style="width:24rem" required>
    <input name="secret" placeholder="signing secret (optional)">
    <button>Save webhook</button>
  </form>
  <pre id="out" class="out" hidden></pre>
</section>
<section class="card">
  <h2>Test delivery</h2>
  <p class="muted">Send the sample event payload to a target and inspect the response.</p>
  <form id="t">
    <input name="url" placeholder="https://endpoint.example.com/hook" style="width:24rem" required>
    <select name="event">
      <?php foreach (vk_webhook_events() as $ev): ?><option><?=vk_h($ev)?></option><?php endforeach; ?>
    </select>
    <button>Send test</button>
  </form>
  <pre id="tout" class="out" hidden></pre>
</section>
<script>
document.getElementById('f').addEventListener('submit', async e => {
  e.preventDefault();
  const b = Object.fromEntries(new FormData(e.target).entries());
  const r = await fetch('/api/webhooks.php', {method:'POST', headers:{'Content-Type':'application/json'}, body: JSON.stringify(b)});
  const o = document.getElementById('out'); o.hidden = false; o.textContent = JSON.stringify(await r.json(), null, 2);
  setTimeout(() => location.reload(), 800);
});
document.getElementById('t').addEventListener('submit', async e => {
  e.preventDefault();
  const b = Object.fromEntries(new FormData(e.target).entries());
  const r = await fetch('/api/webhook_test.php', {method:'POST', headers:{'Content-Type':'application/json'}, body: JSON.stringify(b)});
  const o = document.getElementById('tout'); o.hidden = false; o.textContent = JSON.stringify(await r.json(), null, 2);
});
</script>
<?php vk_page_foot();
