<?php



class VkReportWidget {
    public $title = '';
    public $rows  = [];
    public function __toString(): string {
        return json_encode(['title' => $this->title, 'rows' => count($this->rows)]);
    }
}

class VkHookRegistry {
    public $hooks = [];
    public function __wakeup(): void {
        
        $this->hooks = array_values(array_filter((array) $this->hooks, 'is_string'));
    }
}

class VkProgressMeter {
    public $done  = 0;
    public $total = 0;
    public function __destruct() {
        
    }
    public function pct(): int {
        return $this->total > 0 ? (int) round(100 * $this->done / $this->total) : 0;
    }
}

class VkNoticeBanner {
    public $message = '';
    public function __invoke() { return $this->message; }
}

class VkRetryPolicy {
    public $attempts = 3;
    public $backoff  = 'exponential';
    public function __call($name, $args) { return null; }
}
