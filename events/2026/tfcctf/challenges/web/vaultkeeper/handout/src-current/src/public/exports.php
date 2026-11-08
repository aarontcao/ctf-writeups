<?php

require_once __DIR__ . '/../lib/nav.php';
require_once __DIR__ . '/../lib/exports.php';

$reports = vk_export_catalog();
vk_page_head('Reports & exports', '/exports.php');
?>
<section class="card">
  <p class="muted">Rendered operational reports. Each report has a signed link that lets an
     integrator fetch it without a console session.</p>
  <table class="jobs"><thead><tr><th>Report</th><th>Size</th><th>Link</th></tr></thead><tbody>
    <?php foreach ($reports as $r): ?>
      <tr>
        <td><?=vk_h($r['name'])?></td>
        <td><?=number_format($r['bytes'])?> B</td>
        <td><a href="<?=vk_h($r['href'])?>">download</a></td>
      </tr>
    <?php endforeach; ?>
  </tbody></table>
</section>
<section class="card">
  <h2>Signed links</h2>
  <p class="muted">Links carry an <code>md5(secret · name)</code> signature so they can be shared
     out-of-band. Rotate the export secret to invalidate all outstanding links.</p>
</section>
<?php vk_page_foot();
