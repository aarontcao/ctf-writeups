#!/usr/bin/env python3
"""
Submit one explicit list of flags, with no shared checkpoint.
It reuses `ctf.request()`, so it never reads or prints the session token.
Rejection matching is copied from `fastsweep.py`

Usage:
```
submit_list.py <slug> <flagfile>
```
"""
import os
import sys
import time

sys.path.insert(0, os.path.expanduser("~/.claude/scripts"))
import ctf  # noqa: E402

REJECT_MARKERS = ("invalid_flag", "incorrect", "wrong flag")


def transient(status, text):
    """A fault to retry, as opposed to an answer about the flag."""
    if status == 0 or status >= 500 or status == 429:
        return True
    low = text.lower()
    return "network:" in low or "timed out" in low


def main():
    if len(sys.argv) != 3:
        print(__doc__)
        return 2
    slug, path = sys.argv[1], sys.argv[2]

    ev = ctf.current_event()
    m = ev.find(slug)
    challenge_id = m.get("challenge_id")
    flags = m.get("flags") or []
    unsolved = [f for f in flags if not (f.get("solved") or f.get("captured"))]
    if not unsolved and flags:
        print("already solved: every flag on %s reports captured" % slug)
        return 0
    flag_id = (unsolved or flags)[0].get("flag_id")
    print("challenge_id %s  flag_id %s" % (challenge_id, flag_id))

    with open(path) as fh:
        cands = [ln.strip() for ln in fh if ln.strip()]
    print("submitting %d flags from %s" % (len(cands), path))

    for i, flag in enumerate(cands, 1):
        backoff = 1.0
        for _ in range(5):
            status, payload = ctf.request(
                "POST", "/challenge/submit",
                body={"challenge_id": challenge_id, "flag_id": flag_id,
                      "flag": flag},
                timeout=60)
            text = str(payload)
            if transient(status, text):
                time.sleep(backoff)
                backoff = min(backoff * 2, 20.0)
                continue
            if status == 400 and any(k in text.lower() for k in REJECT_MARKERS):
                print("[%2d/%2d] rejected  %s" % (i, len(cands), flag),
                      flush=True)
                break
            print()
            print("=== NOT A REJECTION, stopping for inspection ===")
            print("flag:   %s" % flag)
            print("status: %s" % status)
            print("body:   %s" % text[:600])
            with open(os.path.join(os.path.dirname(path),
                                   "submit_list.hit"), "w") as out:
                out.write(flag + "\n")
            return 0
        else:
            print("[%2d/%2d] SKIPPED after 5 transient faults  %s"
                  % (i, len(cands), flag), flush=True)
        time.sleep(0.15)

    print()
    print("=== all %d rejected ===" % len(cands))
    return 0


if __name__ == "__main__":
    sys.exit(main())
