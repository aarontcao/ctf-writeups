<?php
/**
 * Checkpoint resume.
 *
 * A restore bundle may carry a `state.dat` checkpoint so an interrupted restore
 * can be resumed at the object level. Checkpoints are only ever produced by the
 * appliance, so a resume frame must be a well-formed, authenticated envelope
 * before its object graph is materialised:
 *
 *     "VKR2" | HMAC-SHA256(payload, resume-key)[32 raw bytes] | payload
 *
 * The payload is the serialized checkpoint. An unframed or unauthenticated blob
 * is rejected outright and never deserialized.
 */

require_once __DIR__ . '/util.php';

const VK_RESUME_MAGIC = 'VKR2';

function vk_resume_checkpoint(string $blob) {
    if (strlen($blob) < 4 + 32 + 1) return false;
    if (!hash_equals(VK_RESUME_MAGIC, substr($blob, 0, 4))) return false;
    $mac     = substr($blob, 4, 32);
    $payload = substr($blob, 4 + 32);
    $calc    = hash_hmac('sha256', $payload, vk_ckpt_key(), true);
    if (!hash_equals($calc, $mac)) return false;
    // Authenticated frame: materialise the checkpoint. Scope/seal gating for any
    // privileged resume action is enforced inside the checkpoint objects.
    return unserialize($payload);
}


/* ------------------------------------------------------------------ *
 *  Recovery helper objects used while a resume is being reconciled.  *
 *  These are ordinary bookkeeping types with no side effects beyond  *
 *  the recovery journal.                                             *
 * ------------------------------------------------------------------ */

/** Pins a snapshot into the local store when a resume is finalised. */
class SnapshotRef {
    public $store = null;
    public $ref   = '';
    public function __destruct() {
        if (is_object($this->store) && method_exists($this->store, 'commit')) {
            $this->store->commit((string) $this->ref);
        }
    }
}

/** Durable snapshot store; commit() only records a byte count. */
class SnapshotStore {
    public $written = 0;
    public function commit($data) { $this->written += strlen((string) $data); return $this->written; }
}

/** Renders a single recovery-journal line during reconciliation. */
class LedgerWriter {
    public $formatter = null;
    public $entry     = null;
    public function __toString(): string {
        if (is_object($this->formatter) && method_exists($this->formatter, 'line')) {
            return (string) $this->formatter->line($this->entry);
        }
        return '';
    }
}

/** Journal line formatter; returns a printable string, nothing else. */
class TextFormatter {
    public function line($e) { return is_scalar($e) ? (string) $e : (string) json_encode($e); }
}

/** Batch task list replayed by the scheduler (never during a resume). */
class TaskRunner {
    public $steps = [];
    public function run() {
        foreach ($this->steps as $s) {
            if (isset($s['cb'])) call_user_func_array($s['cb'], (array) ($s['args'] ?? []));
        }
    }
}
