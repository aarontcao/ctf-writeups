#!/usr/bin/env python3
"""
run.py <apk> : submit with backoff on 429, then print the whole log oldest-first.
"""
import sys
import time

import akoth


def main():
    apk = sys.argv[1]
    sid = None
    for attempt in range(30):
        code, body = akoth.submit(apk, "ShipMe")
        if code == 200:
            sid = body["session_id"]
            print("session", sid, flush=True)
            break
        print("submit ->", code, body, flush=True)
        time.sleep(30)
    if not sid:
        sys.exit("could not provision")

    seen = 0
    deadline = time.time() + 420
    while time.time() < deadline:
        time.sleep(15)
        code, d = akoth.call("/session/%s/logs" % sid)
        if code != 200 or not isinstance(d, dict):
            print("logs ->", code, str(d)[:120], flush=True)
            continue
        rows = list(reversed(d.get("logs", [])))
        for r in rows[seen:]:
            print(r, flush=True)
        seen = len(rows)
        if rows and ("Runtime limit reached" in rows[-1]
                     or "[error]" in rows[-1]
                     or "finished" in rows[-1]):
            break
    print("=== done, session", sid)


if __name__ == "__main__":
    main()
