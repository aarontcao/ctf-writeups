<?php

class CacheShard implements ArrayAccess {
    public $reconcile = null;   
    public function offsetSet($k, $v): void {
        if ($this->reconcile !== null) {
            $record = (string) $this->reconcile;
        }
    }
    public function offsetExists($k): bool { return false; }
    public function offsetGet($k): mixed   { return null; }
    public function offsetUnset($k): void  {}
}


class ManifestCursor implements Iterator {
    public $fragments = [];
    private $i = 0;
    public function current(): mixed { return implode('', $this->fragments); }
    public function key(): mixed     { return $this->i; }
    public function next(): void     { $this->i++; }
    public function rewind(): void   { $this->i = 0; }
    public function valid(): bool    { return $this->i < 1; }
}
