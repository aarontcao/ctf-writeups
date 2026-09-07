#!/usr/bin/env python3
# Tiny HTTP server that answers every request with a non-standard status code
# plus a Location header, so PHP's http wrapper (follow_location=1 set
# explicitly) follows it while fetch_source.php flags the chain as "unusual"
# and dumps the final body.
import sys, socket, threading

PORT = int(sys.argv[1]) if len(sys.argv) > 1 else 9999

def handle(c):
    try:
        c.settimeout(5)
        data = b''
        while b'\r\n\r\n' not in data:
            b = c.recv(4096)
            if not b: break
            data += b
        line = data.split(b'\r\n')[0].decode('latin1')
        path = line.split(' ')[1] if len(line.split(' ')) > 1 else '/'
        target = path[3:] if path.startswith('/r/') else 'http://127.0.0.1/api/status.php'
        resp = ("HTTP/1.1 418 Teapot\r\n"
                "Location: %s\r\n"
                "Content-Length: 0\r\n"
                "Connection: close\r\n\r\n" % target).encode()
        c.sendall(resp)
    except Exception as e:
        pass
    finally:
        try: c.close()
        except Exception: pass

s = socket.socket()
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind(('0.0.0.0', PORT))
s.listen(64)
print('listening on %d' % PORT, flush=True)
while True:
    c, a = s.accept()
    threading.Thread(target=handle, args=(c,), daemon=True).start()
