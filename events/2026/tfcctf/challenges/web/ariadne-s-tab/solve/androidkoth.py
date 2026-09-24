#!/usr/bin/env python3
"""
androidkoth: talk to the TFC CTF 2026 Android solve-APK platform.

The platform authenticates with the TEAM TOKEN in an X-Auth header. The token
is read from `pass secrets/tfcctf/invite` and is NEVER printed.

    androidkoth login
    androidkoth challenges
    androidkoth sessions
    androidkoth provision <challenge> <file.apk>
    androidkoth logs <session_id>
    androidkoth status <session_id>
"""

import json
import mimetypes
import os
import subprocess
import sys
import urllib.error
import urllib.request
import uuid

BASE = "https://android.koth.pro"
PASS_ENTRY = "secrets/tfcctf/invite"


def die(msg, code=1):
    print(f"androidkoth: {msg}", file=sys.stderr)
    raise SystemExit(code)


def team_token():
    out = subprocess.run(
        ["pass", "show", PASS_ENTRY], capture_output=True, text=True, timeout=30
    )
    if out.returncode != 0 or not out.stdout.strip():
        die("pass show failed; unlock gpg-agent in an interactive shell")
    return out.stdout.strip().splitlines()[0]


def call(path, method="GET", body=None, ctype=None):
    req = urllib.request.Request(BASE + path, method=method, data=body)
    req.add_header("X-Auth", team_token())
    req.add_header("Accept", "application/json, text/plain, */*")
    req.add_header(
        "User-Agent",
        "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) "
        "Chrome/128.0.0.0 Safari/537.36",
    )
    req.add_header("Accept-Language", "en-US,en;q=0.9")
    req.add_header("Origin", BASE)
    req.add_header("Referer", BASE + "/")
    if ctype:
        req.add_header("Content-Type", ctype)
    try:
        with urllib.request.urlopen(req, timeout=120) as resp:
            raw = resp.read()
            status = resp.status
    except urllib.error.HTTPError as exc:
        raw = exc.read()
        status = exc.code
    except Exception as exc:
        die(f"request failed: {exc}")
    try:
        return status, json.loads(raw)
    except Exception:
        return status, raw.decode("utf-8", "replace")


def multipart(fields, files):
    boundary = uuid.uuid4().hex
    out = b""
    for k, v in fields.items():
        out += f"--{boundary}\r\nContent-Disposition: form-data; name=\"{k}\"\r\n\r\n{v}\r\n".encode()
    for k, path in files.items():
        name = os.path.basename(path)
        mime = mimetypes.guess_type(name)[0] or "application/vnd.android.package-archive"
        with open(path, "rb") as handle:
            data = handle.read()
        out += (
            f"--{boundary}\r\nContent-Disposition: form-data; name=\"{k}\"; "
            f"filename=\"{name}\"\r\nContent-Type: {mime}\r\n\r\n"
        ).encode()
        out += data + b"\r\n"
    out += f"--{boundary}--\r\n".encode()
    return out, f"multipart/form-data; boundary={boundary}"


def main(argv):
    if not argv:
        print(__doc__)
        return 1
    cmd, rest = argv[0], argv[1:]
    if cmd == "login":
        print(json.dumps(call("/login"), indent=2))
    elif cmd == "challenges":
        print(json.dumps(call("/challenges"), indent=2))
    elif cmd == "sessions":
        print(json.dumps(call("/sessions"), indent=2))
    elif cmd == "provision":
        challenge, apk = rest[0], rest[1]
        body, ctype = multipart({"challenge": challenge}, {"file": apk})
        print(json.dumps(call("/provision", "POST", body, ctype), indent=2))
    elif cmd == "logs":
        print(json.dumps(call(f"/session/{rest[0]}/logs"), indent=2))
    elif cmd == "status":
        print(json.dumps(call(f"/session/{rest[0]}/status"), indent=2))
    elif cmd == "raw":
        print(json.dumps(call(rest[0]), indent=2))
    else:
        die(f"unknown command {cmd}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
