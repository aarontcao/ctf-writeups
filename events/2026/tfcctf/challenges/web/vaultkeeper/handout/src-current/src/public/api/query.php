<?php





require_once __DIR__ . '/../../lib/util.php';
require_once __DIR__ . '/../../lib/search.php';
require_once __DIR__ . '/../../lib/request.php';

if (vk_method() === 'POST') {
    $in = vk_input();
    if (empty($in['filter'])) vk_json(['error' => 'filter required'], 400);
    vk_json(['ok' => true, 'search' => vk_saved_search_save($in)]);
}

$filter = (string) ($_GET['filter'] ?? '');
if (!empty($_GET['id'])) {
    foreach (vk_saved_searches() as $s) {
        if (($s['id'] ?? '') === $_GET['id']) { $filter = (string) $s['filter']; break; }
    }
}
if ($filter === '' && !isset($_GET['filter'])) {
    vk_json(['saved' => vk_saved_searches()]);
}
vk_json(['filter' => $filter] + vk_run_catalog_search($filter));
