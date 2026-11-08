<?php


$to = (string) ($_GET['to'] ?? '/');
if (preg_match('#^/(?!/)[A-Za-z0-9_./?=&%\-]*$#', $to)) {
    header('Location: ' . $to, true, 302);
    echo 'redirecting…';
} else {
    header('Content-Type: text/html; charset=utf-8');
    echo '<!doctype html><meta charset=utf-8><link rel=stylesheet href=/assets/style.css>';
    echo '<div class="wrap"><div class="card"><h2>External link</h2>';
    echo '<p class=muted>This link points outside Vaultkeeper and was not opened automatically.</p>';
    echo '<p><a href="/">Return to console</a></p></div></div>';
}
