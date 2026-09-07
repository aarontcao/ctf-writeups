<?php

$doc   = $_GET['doc']   ?? 'help';
$title = htmlspecialchars((string) ($_GET['title'] ?? 'Documentation'), ENT_QUOTES, 'UTF-8');
$safe  = basename($doc);                       
$path  = __DIR__ . "/docs/$safe.html";
header('Content-Type: text/html');
echo "<!doctype html><meta charset=utf-8><link rel=stylesheet href=/assets/style.css>";
echo "<div class='wrap'><div class='card'><h1>$title</h1>";   
if (is_file($path)) { readfile($path); } else { echo "<p class=muted>Document not found.</p>"; }
echo "</div></div>";
