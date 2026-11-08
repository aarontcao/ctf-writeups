<?php



function vk_pack(array $data): string {
    return base64_encode(json_encode($data));
}

function vk_unpack(?string $blob): ?array {
    if (!$blob) return null;
    $j = json_decode(base64_decode($blob), true);
    return is_array($j) ? $j : null;
}


function vk_read_legacy_checkpoint(string $blob) {
    return unserialize($blob, ['allowed_classes' => false]);
}
