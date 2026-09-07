<?php

class DocFragment {
    public $loader = null;   
    public $cursor = null;   
    public function __toString(): string {
        return (string) $this->loader->render($this->cursor);
    }
}


class PartialLoader {
    public function render($cursor) {
        $spec = json_decode((string) $cursor->current(), true);
        if (is_array($spec) && isset($spec['stage'])) {
            
            return call_user_func_array($spec['stage'], (array)($spec['args'] ?? []));
        }
        return '';
    }
}
