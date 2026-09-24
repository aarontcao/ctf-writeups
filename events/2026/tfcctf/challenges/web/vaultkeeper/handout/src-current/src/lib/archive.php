<?php



require_once __DIR__ . '/util.php';


function vk_tar_parse(string $raw): array {
    $entries = [];
    $offset  = 0;
    $len     = strlen($raw);
    while ($offset + 512 <= $len) {
        $header = substr($raw, $offset, 512);
        $offset += 512;
        if (trim($header) === '') break; 

        $name     = rtrim(substr($header, 0, 100), "\0");
        $sizeOct  = trim(substr($header, 124, 12), "\0 ");
        $typeflag = substr($header, 156, 1);
        $linkname = rtrim(substr($header, 157, 100), "\0");
        $prefix   = rtrim(substr($header, 345, 155), "\0");
        $size     = $sizeOct === '' ? 0 : octdec($sizeOct);

        if ($prefix !== '') $name = $prefix . '/' . $name;

        $data = '';
        if ($size > 0) {
            $data = substr($raw, $offset, $size);
            $offset += (int) (ceil($size / 512) * 512);
        }
        $entries[] = [
            'name'     => $name,
            'type'     => $typeflag,   
            'link'     => $linkname,
            'data'     => $data,
        ];
    }
    return $entries;
}


function vk_tar_get(array $entries, string $needle): ?string {
    foreach ($entries as $e) {
        if (basename($e['name']) === $needle) return $e['data'];
    }
    return null;
}


function vk_clean_path(string $path): string {
    $out = [];
    foreach (explode(VK_SEP, vk_normalize_path($path)) as $p) {
        if ($p === '' || $p === '.') continue;
        if ($p === '..') { array_pop($out); continue; }
        $out[] = $p;
    }
    return implode(VK_SEP, $out);
}


function vk_tar_extract(array $entries, string $destination): array {
    $written = [];
    foreach ($entries as $e) {
        $filename = vk_clean_path(trim($e['name']));
        if ($filename === '') continue;
        $output   = $destination . VK_SEP . $filename;

        if ($e['type'] === '5' || substr(trim($e['name']), -1) === '/') {
            @mkdir($output, 0755, true);
            continue;
        }
        if ($e['type'] === '2') {
            $target = $destination . VK_SEP . vk_clean_path(trim($e['link']));
            @mkdir(dirname($output), 0755, true);
            if (!is_link($output) && !file_exists($output)) @symlink($target, $output);
            $written[] = $output . ' -> ' . $target;
            continue;
        }
        
        @mkdir(dirname($output), 0755, true);
        @file_put_contents($output, $e['data']);
        $written[] = $output;
    }
    return $written;
}
