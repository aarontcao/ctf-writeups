<?php




function vk_uuid4(): string {
    $b = random_bytes(16);
    $b[6] = chr((ord($b[6]) & 0x0f) | 0x40);
    $b[8] = chr((ord($b[8]) & 0x3f) | 0x80);
    return vsprintf('%s%s-%s-%s-%s-%s%s%s', str_split(bin2hex($b), 4));
}

function vk_ulid(): string {
    $t   = (int) (microtime(true) * 1000);
    $enc = '0123456789ABCDEFGHJKMNPQRSTVWXYZ';
    $out = '';
    for ($i = 9; $i >= 0; $i--) { $out .= $enc[($t >> ($i * 5)) & 31]; }
    for ($i = 0; $i < 16; $i++) { $out .= $enc[random_int(0, 31)]; }
    return $out;
}

function vk_snowflake(int $worker = 1): string {
    static $seq = 0;
    $ms  = (int) (microtime(true) * 1000);
    $seq = ($seq + 1) & 0xfff;
    return (string) ((($ms & 0x1FFFFFFFFFF) << 22) | (($worker & 0x3ff) << 12) | $seq);
}

function vk_short_ref(string $seed = ''): string {
    return substr(hash('sha1', $seed . random_bytes(8)), 0, 12);
}
