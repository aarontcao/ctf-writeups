<?php




require_once __DIR__ . '/util.php';


enum VkScope: string {
    case Guest    = 'guest';
    case Operator = 'operator';
}


final class VkSealContext {
    public function __construct(
        public readonly string $slot,
        public readonly mixed  $sink,
        public readonly string $mac
    ) {}
}

class RestorePoint {
    public $dirty = false;
    public $scope = null;   
    public $ctx   = null;   
    public $snapshot = '';

    private const SEAL_CTX = 'vk-checkpoint-seal.v5';

    public function __unserialize(array $s): void {
        $this->scope    = $s['scope'] ?? null;
        $this->ctx      = $s['ctx'] ?? null;
        $this->snapshot = $s['snapshot'] ?? '';
        
        if ($this->scope !== VkScope::Operator) return;
        if (!$this->ctx instanceof VkSealContext) return;
        
        $mac = hash_hmac('sha256',
            self::SEAL_CTX . '|' . $this->ctx->slot . '|' . get_class($this->ctx->sink),
            vk_seal_key());
        if (hash_equals($mac, $this->ctx->mac)) {
            $this->dirty = true;
        }
    }
    public function __destruct() {
        if ($this->dirty && $this->ctx instanceof VkSealContext && $this->ctx->sink !== null) {
            $this->ctx->sink[$this->ctx->slot] = $this->snapshot;
        }
    }
}
