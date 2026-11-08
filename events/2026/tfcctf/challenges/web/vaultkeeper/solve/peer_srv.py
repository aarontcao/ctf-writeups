#!/usr/bin/env python3
"""Redirector and fake cluster peer that logs what peer_probe.php and webhook_test.php
send. Routes: /r/<url> and /R/<b64url> answer 418 + Location, /S/<code>/<b64url>
picks the status, /j/<b64url> returns that JSON, and /slow/<secs> stalls."""
import base64
import json
import os
import socket
import sys
import threading
import time

PORT = int(sys.argv[1]) if len(sys.argv) > 1 else 9998
HERE = os.path.dirname(os.path.abspath(__file__))
LOGF = os.path.join(HERE, "peer_srv.log")

# peer_probe echoes $j['version'] or $j['node'] if it matches ^[\w.\-]{1,32}$
DEFAULT_PEER = {
    "service": "vk-keyring",
    "appliance": "vaultkeeper",
    "version": "4.2.1",
    "node": "node-b",
    "slot": "operator",
    "seal": "open",
    "unseal": "ok",
    "handshake": "ok",
    "peer_ok": True,
    "alg": "aes-128-gcm",
}


def b64d(s):
    s = s.strip()
    return base64.urlsafe_b64decode(s + "=" * (-len(s) % 4)).decode("utf-8", "replace")


def log(entry):
    entry["t"] = time.time()
    line = json.dumps(entry)
    with open(LOGF, "a") as f:
        f.write(line + "\n")
    print("[<] " + line[:600], flush=True)


def respond(c, code, reason, headers, body=b""):
    head = "HTTP/1.1 %d %s\r\n" % (code, reason)
    for k, v in headers:
        head += "%s: %s\r\n" % (k, v)
    head += "Content-Length: %d\r\nConnection: close\r\n\r\n" % len(body)
    c.sendall(head.encode("latin1") + body)


def handle(c, addr):
    try:
        c.settimeout(8)
        data = b""
        while b"\r\n\r\n" not in data and len(data) < 65536:
            chunk = c.recv(4096)
            if not chunk:
                break
            data += chunk
        if not data:
            return
        head, _, rest = data.partition(b"\r\n\r\n")
        lines = head.decode("latin1").split("\r\n")
        reqline = lines[0]
        headers = {}
        for h in lines[1:]:
            if ":" in h:
                k, v = h.split(":", 1)
                headers[k.strip().lower()] = v.strip()
        # read the body so a webhook_test POST is logged
        clen = int(headers.get("content-length", "0") or 0)
        body = rest
        while len(body) < clen and len(body) < 262144:
            chunk = c.recv(4096)
            if not chunk:
                break
            body += chunk
        parts = reqline.split(" ")
        method = parts[0] if parts else "?"
        path = parts[1] if len(parts) > 1 else "/"
        log({"peer": addr[0], "req": reqline, "method": method, "path": path,
             "headers": headers, "body": body.decode("utf-8", "replace")[:4000]})

        if path.startswith("/r/"):
            respond(c, 418, "Teapot", [("Location", path[3:])])
        elif path.startswith("/R/"):
            respond(c, 418, "Teapot", [("Location", b64d(path[3:].split("?")[0]))])
        elif path.startswith("/S/"):
            _, _, code, enc = path.split("/", 3)
            respond(c, int(code), "X", [("Location", b64d(enc.split("?")[0]))])
        elif path.startswith("/j/"):
            payload = b64d(path[3:].split("?")[0]).encode()
            respond(c, 200, "OK", [("Content-Type", "application/json")], payload)
        elif path.startswith("/slow/"):
            time.sleep(min(20.0, float(path.split("/")[2].split("?")[0])))
            respond(c, 200, "OK", [("Content-Type", "application/json")], b"{}")
        else:
            payload = json.dumps(DEFAULT_PEER).encode()
            respond(c, 200, "OK", [("Content-Type", "application/json")], payload)
    except Exception as e:  # noqa: BLE001
        try:
            log({"peer": addr[0], "error": repr(e)})
        except Exception:
            pass
    finally:
        try:
            c.close()
        except Exception:
            pass


def main():
    s = socket.socket()
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind(("0.0.0.0", PORT))
    s.listen(128)
    print("peer_srv listening on %d, log %s" % (PORT, LOGF), flush=True)
    while True:
        c, a = s.accept()
        threading.Thread(target=handle, args=(c, a), daemon=True).start()


if __name__ == "__main__":
    main()
