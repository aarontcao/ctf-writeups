<?php

require_once __DIR__ . '/../../lib/util.php';

$name = basename((string) ($_GET['name'] ?? 'help'));   
$path = __DIR__ . '/../docs/' . $name . '.html';
if (!is_file($path)) vk_json(['error' => 'not found'], 404);
vk_json(['name' => $name, 'html' => file_get_contents($path)]);
