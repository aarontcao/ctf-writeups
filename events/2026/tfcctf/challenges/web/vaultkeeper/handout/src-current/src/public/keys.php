<?php

require_once __DIR__ . '/../lib/nav.php';
require_once __DIR__ . '/../lib/keys.php';

vk_page_head('Encryption keys', '/keys.php');
?>
<section class="card">
  <p class="muted">Envelope keys protect snapshots at rest. Data keys are wrapped by the
     appliance root key. Raw key material is held by the appliance and is never
     exported through the console or API.</p>
  <?php vk_table(vk_keys(), [
      'label' => 'Key', 'algo' => 'Algorithm', 'purpose' => 'Purpose',
      'state' => 'State', 'version' => 'Version', 'rotated' => 'Last rotated']); ?>
</section>
<section class="card">
  <h2>Wrap test</h2>
  <p class="muted">Confirm a key is usable: the sample is sealed with the appliance key and
     only the ciphertext is returned.</p>
  <form id="w">
    <input name="sample" placeholder="sample plaintext" value="healthcheck">
    <button>Wrap</button>
  </form>
  <pre id="out" class="out" hidden></pre>
</section>
<script>
document.getElementById('w').addEventListener('submit', async e => {
  e.preventDefault();
  const b = Object.fromEntries(new FormData(e.target).entries());
  const r = await fetch('/api/keys.php?wrap=1', {method:'POST', headers:{'Content-Type':'application/json'}, body: JSON.stringify(b)});
  const o = document.getElementById('out'); o.hidden = false; o.textContent = JSON.stringify(await r.json(), null, 2);
});
</script>
<?php vk_page_foot();
