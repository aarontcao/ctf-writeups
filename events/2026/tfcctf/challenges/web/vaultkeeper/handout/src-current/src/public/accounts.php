<?php

require_once __DIR__ . '/../lib/nav.php';
require_once __DIR__ . '/../lib/accounts.php';

$rollup = vk_member_rollup();
vk_page_head('Access control', '/accounts.php');
?>
<section class="card">
  <div class="stat-row">
    <?php foreach (vk_member_roles() as $r): ?>
      <div class="stat"><b><?=(int)($rollup[$r] ?? 0)?></b><span><?=vk_h($r)?>s</span></div>
    <?php endforeach; ?>
  </div>
  <p class="muted">Console members sign in to manage the appliance. Roles govern console
     access only; restore-job scope is granted per job. New invitees start as
     <code>viewer</code> — an admin promotes from there.</p>
  <?php vk_table(vk_members(), [
      'name' => 'Name', 'email' => 'Email', 'role' => 'Role',
      'status' => 'Status', 'mfa' => 'MFA', 'last_seen' => 'Last seen']); ?>
</section>
<section class="card">
  <h2>Active sessions</h2>
  <?php
    require_once __DIR__ . '/../lib/sessions.php';
    vk_table(vk_console_sessions(), ['member' => 'Member', 'role' => 'Role', 'ip' => 'IP', 'agent' => 'Client', 'started' => 'Started', 'mfa' => 'MFA']);
  ?>
</section>
<section class="card">
  <h2>Invite member</h2>
  <form id="f">
    <input name="name" placeholder="full name" required>
    <input name="email" placeholder="email" required>
    <select name="role"><option>viewer</option><option>operator</option><option>maintainer</option><option>admin</option></select>
    <button>Send invite</button>
  </form>
  <p class="muted">Role selection is a request; the seated role is set on acceptance.</p>
  <pre id="out" class="out" hidden></pre>
</section>
<script>
document.getElementById('f').addEventListener('submit', async e => {
  e.preventDefault();
  const b = Object.fromEntries(new FormData(e.target).entries());
  const r = await fetch('/api/accounts.php', {method:'POST', headers:{'Content-Type':'application/json'}, body: JSON.stringify(b)});
  const o = document.getElementById('out'); o.hidden = false; o.textContent = JSON.stringify(await r.json(), null, 2);
  setTimeout(() => location.reload(), 800);
});
</script>
<?php vk_page_foot();
