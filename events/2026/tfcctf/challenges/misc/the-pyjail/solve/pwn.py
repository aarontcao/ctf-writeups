#!/usr/bin/env python3
"""
Claim a python-jail instance, fire the exploit, release the slot at once.

The platform bundle (main-JPWEKMMU.js) builds the connection string as

    connection_type == "nodeport"  ->  nc <connection.host|ip> <ports[0].tcpPort>
    connection_type == "http"      ->  https://<name>.challs.ctf.thefewchosen.com
    otherwise (netcat)             ->  ncat --ssl <name>.challs... 1337

The pyjail is "nodeport", so it's RAW TCP on an allocated node port, with no
TLS and no SNI.  The host and port only appear in GET /isolated once the pod is
allocated, so poll for them.

Endpoints:  POST /isolated {"name": image}   GET /isolated   DELETE /isolated/<deployment>
Team cap is three concurrent instances, so this releases as soon as it's done.
"""
import json
import os
import re
import ssl
import subprocess
import sys
import time
import urllib.error
import urllib.request

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import solve as solver  # noqa: E402

API = 'https://challenge-manager.management.ctf.thefewchosen.com/isolated'
IMAGE = 'python-jail'
TOKEN_FILE = os.path.expanduser('~/.config/ctf/token.json')
FLAG_RE = re.compile(rb'TFCCTF\{[^}\n]*\}')


def token():
    return json.load(open(TOKEN_FILE))['token']


def api(method, path='', body=None):
    url = API + path
    data = json.dumps(body).encode() if body is not None else None
    req = urllib.request.Request(url, data=data, method=method)
    req.add_header('Authorization', 'Bearer ' + token())
    req.add_header('content-type', 'application/json')
    ctx = ssl.create_default_context()
    try:
        with urllib.request.urlopen(req, timeout=25, context=ctx) as r:
            return r.status, json.loads(r.read() or b'{}')
    except urllib.error.HTTPError as e:
        raw = e.read()
        try:
            return e.code, json.loads(raw or b'{}')
        except Exception:
            return e.code, {'raw': raw[:200].decode('utf-8', 'replace')}
    except Exception as e:
        return 0, {'error': repr(e)}


def endpoint_of(entry):
    conn = entry.get('connection') or {}
    host = conn.get('host') or conn.get('ip')
    ports = conn.get('ports') or []
    if host and ports:
        p = ports[0]
        return host, p.get('tcpPort') or p.get('port')
    return None, None


def refresh_token():
    """The access token lasts 600 seconds; ctf.py knows how to renew it."""
    sys.path.insert(0, os.path.expanduser('~/.claude/scripts'))
    try:
        import ctf as ctfcli
        return ctfcli.refresh_access() or ctfcli.relogin_quietly()
    except Exception as e:
        print('[!] token refresh failed: %r' % e)
        return False


def existing():
    """Reuse a python-jail instance somebody else already started."""
    st, body = api('GET')
    if 200 <= st < 300:
        for e in body.get('data', []):
            if str(e.get('name', '')).startswith(IMAGE + '-'):
                return e.get('name')
    return None


def claim(deadline):
    """Poll until a slot frees, then take it. Returns (name, mine)."""
    while time.time() < deadline:
        got = existing()
        if got:
            print('[+] reusing existing instance %s' % got)
            return got, False
        st, body = api('POST', body={'name': IMAGE})
        if st == 401:
            print('[.] 401, refreshing token')
            refresh_token()
        if st == 0:
            print('[!] transport: %s' % body.get('error'))
        elif 200 <= st < 300:
            name = body.get('deploymentName') or body.get('name') or body.get('data')
            print('[+] claimed %s  (%s)' % (name, body))
            # For a nodeport challenge the connection comes back in the POST
            # body.  GET /isolated returns only name and expiresAt, so a driver
            # that waits for it there loops forever.  That's what cost rivers
            # an hour.  Stash it so wait_endpoint can skip the poll entirely.
            global POST_CONN
            POST_CONN = body.get('connection') or {}
            return name, True
        else:
            print('[.] %s %s' % (st, body.get('error') or body))
        time.sleep(10)
    return None, False


POST_CONN = {}

# The fd exfil through sys.remote_exec works locally and doesn't land on the
# real pod: three remote runs all returned "Running your code..." and no flag.
# PYJAIL_CMD lets the caller swap in an outbound channel instead, without
# touching the escape itself, which is already proven.
CMD = os.environ.get('PYJAIL_CMD') or ''


def wait_endpoint(name, deadline):
    host = POST_CONN.get('host') or POST_CONN.get('ip')
    ports = POST_CONN.get('ports') or []
    if host and ports:
        p = ports[0]
        port = p.get('tcpPort') or p.get('port')
        print('[+] endpoint from the POST body: %s:%s' % (host, port))
        return host, port
    while time.time() < deadline:
        st, body = api('GET')
        if 200 <= st < 300:
            for e in body.get('data', []):
                if e.get('name') == name:
                    h, p = endpoint_of(e)
                    if h and p:
                        return h, p
                    print('[.] allocating ports... %s' % json.dumps(e)[:200])
        time.sleep(5)
    return None, None


def release(name):
    st, body = api('DELETE', '/' + name)
    print('[*] release %s -> %s %s' % (name, st, body))


def main():
    budget = float(sys.argv[1]) if len(sys.argv) > 1 else 900.0
    deadline = time.time() + budget
    name, mine = claim(deadline)
    if not name:
        print('[-] never got a slot inside the budget')
        return 2
    try:
        host, port = wait_endpoint(name, min(deadline, time.time() + 180))
        if not host:
            print('[-] instance never reported an endpoint')
            return 3
        print('[*] endpoint nc %s %s' % (host, port))
        out = b''
        for attempt in range(3):
            try:
                out = solver.run(host, port, cmd=CMD) if CMD else solver.run(host, port)
            except Exception as e:
                print('[!] attempt %d transport error: %r' % (attempt, e))
                time.sleep(3)
                continue
            print('[*] attempt %d got %d bytes: %r' % (attempt, len(out), out[:400]))
            if FLAG_RE.search(out):
                break
            time.sleep(2)
        m = FLAG_RE.search(out)
        art = os.path.join(HERE, '..', 'artifacts', 'remote-run.txt')
        with open(art, 'ab') as f:
            f.write(b'\n--- %s %s:%s ---\n' % (time.strftime('%FT%TZ', time.gmtime()).encode(),
                                               host.encode(), str(port).encode()))
            f.write(out)
        if m:
            flag = m.group().decode()
            print('[+] FLAG %s' % flag)
            open(os.path.join(HERE, '..', 'scratch', 'FLAG.txt'), 'w').write(flag + '\n')
            subprocess.run([os.path.expanduser('~/bin/ctf'), 'flag', 'the-pyjail', flag])
            return 0
        print('[-] no flag')
        return 1
    finally:
        if mine:
            release(name)      # never release an instance we didn't start
        else:
            print('[*] leaving %s alone, it was not ours' % name)


if __name__ == '__main__':
    sys.exit(main())
