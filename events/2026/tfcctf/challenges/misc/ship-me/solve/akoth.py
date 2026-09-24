#!/usr/bin/env python3
"""
Minimal client for https://android.koth.pro (TFC CTF 2026 Android platform).

  akoth.py submit <apk> [challenge]   upload an APK, print the session id
  akoth.py sessions                   list our sessions
  akoth.py logs <session_id>          fetch stored logs
  akoth.py watch <session_id> [secs]  poll status + logs until finished

Auth is the TEAM TOKEN from `pass secrets/tfcctf/invite`, sent as X-Auth.
The token is never printed.
"""
import json
import mimetypes
import os
import subprocess
import sys
import time
import urllib.error
import urllib.request
import uuid

BASE = "https://android.koth.pro"
UA = "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/128.0 Safari/537.36"


def token():
    out = subprocess.run(["pass", "show", "secrets/tfcctf/invite"],
                         capture_output=True, text=True, timeout=30)
    if out.returncode != 0 or not out.stdout.strip():
        sys.exit("could not read team token from pass")
    return out.stdout.strip().splitlines()[0]


def call(path, method="GET", body=None, ctype=None, timeout=60):
    req = urllib.request.Request(BASE + path, data=body, method=method)
    req.add_header("X-Auth", token())
    req.add_header("User-Agent", UA)
    if ctype:
        req.add_header("Content-Type", ctype)
    try:
        with urllib.request.urlopen(req, timeout=timeout) as r:
            raw = r.read()
            code = r.status
    except urllib.error.HTTPError as e:
        raw, code = e.read(), e.code
    try:
        return code, json.loads(raw)
    except Exception:
        return code, raw.decode("utf-8", "replace")


def submit(apk, challenge):
    b = uuid.uuid4().hex
    with open(apk, "rb") as f:
        data = f.read()
    parts = []
    parts.append(("--" + b + "\r\n"
                  'Content-Disposition: form-data; name="challenge"\r\n\r\n'
                  + challenge + "\r\n").encode())
    parts.append(("--" + b + "\r\n"
                  'Content-Disposition: form-data; name="file"; filename="'
                  + os.path.basename(apk) + '"\r\n'
                  "Content-Type: application/vnd.android.package-archive\r\n\r\n").encode())
    parts.append(data)
    parts.append(("\r\n--" + b + "--\r\n").encode())
    return call("/provision", "POST", b"".join(parts),
                "multipart/form-data; boundary=" + b, timeout=180)


def main():
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    cmd = sys.argv[1]
    if cmd == "me":
        print(call("/login"))
    elif cmd == "challenges":
        print(call("/challenges"))
    elif cmd == "submit":
        ch = sys.argv[3] if len(sys.argv) > 3 else "ShipMe"
        print(submit(sys.argv[2], ch))
    elif cmd == "sessions":
        print(json.dumps(call("/sessions")[1], indent=2)[:4000])
    elif cmd == "logs":
        print(json.dumps(call("/session/%s/logs" % sys.argv[2])[1], indent=2))
    elif cmd == "status":
        print(call("/session/%s/status" % sys.argv[2]))
    elif cmd == "watch":
        sid = sys.argv[2]
        deadline = time.time() + (int(sys.argv[3]) if len(sys.argv) > 3 else 420)
        last = 0
        while time.time() < deadline:
            c, st = call("/session/%s/status" % sid)
            c2, lg = call("/session/%s/logs" % sid)
            rows = lg.get("logs", []) if isinstance(lg, dict) else []
            for r in rows[last:]:
                print(r)
            last = max(last, len(rows))
            s = st.get("status") if isinstance(st, dict) else st
            print("[status] %s  logs=%d" % (s, len(rows)), flush=True)
            if s in ("finished", "failed", "timeout"):
                break
            time.sleep(5)
    else:
        sys.exit(__doc__)


if __name__ == "__main__":
    main()
