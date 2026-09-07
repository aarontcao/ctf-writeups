#!/usr/bin/env python3
"""
Claim exactly ONE bitdebit3-chal instance, exploit it, then release the slot.

Contract agreed with the coordinator on 2026-09-05:
  - GET /isolated answers instantly, POST /isolated routinely takes over 25 s.
    So GET timeout 25 s, POST timeout 90 s. A short POST timeout abandons a
    request that is still in flight and hands the slot to whoever waited longer.
  - Several parallel claim threads, poll every 3 s, back off on 429.
  - After a client side POST timeout, re-check with GET before retrying.
  - Take exactly ONE slot. If two land, delete the spare at once.
  - Delete our instance the moment we have the flag.
"""
import json, urllib.request, urllib.error, time, sys, re, os, threading

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import importlib.util
spec = importlib.util.spec_from_file_location("sb", os.path.join(HERE, "solve-b.py"))
sb = importlib.util.module_from_spec(spec); spec.loader.exec_module(sb)

HOST = 'https://challenge-manager.management.ctf.thefewchosen.com'
IMAGE = 'bitdebit3-chal'

sys.path.insert(0, os.path.expanduser("~/.claude/scripts"))
import ctf as ctfcli

_tlock = threading.Lock()


def get_tok():
    with _tlock:
        try:
            if ctfcli.token_expiring():
                if not ctfcli.refresh_access():
                    ctfcli.relogin_quietly()
        except Exception as e:
            print('refresh failed', e, flush=True)
        return json.load(open(os.path.expanduser("~/.config/ctf/token.json")))['token']


def call(path, method='GET', body=None, timeout=25):
    data = json.dumps(body).encode() if body is not None else None
    req = urllib.request.Request(HOST + path, data=data,
        headers={'content-type': 'application/json',
                 'Authorization': 'Bearer ' + get_tok()}, method=method)
    try:
        r = urllib.request.urlopen(req, timeout=timeout); return r.status, r.read().decode()
    except urllib.error.HTTPError as e: return e.code, e.read().decode()
    except Exception as e: return 0, str(e)


def mine():
    """Names of our running bitdebit instances, via the instant GET."""
    st, b = call('/isolated', timeout=25)
    if st != 200:
        return None
    try:
        return [d['name'] for d in json.loads(b).get('data', []) if d['name'].startswith(IMAGE)]
    except Exception:
        return None


def release(name):
    for path, method, body in [('/isolated', 'DELETE', {"name": name}),
                               ('/isolated/' + name, 'DELETE', None),
                               ('/isolated', 'POST', {"name": name, "action": "stop"})]:
        st, b = call(path, method, body, timeout=40)
        print('release', path, method, st, b[:120], flush=True)
        if 200 <= st < 300:
            return True
    return False


stop = threading.Event()
found = []


def claimer(tag):
    while not stop.is_set():
        st, b = call('/isolated', 'POST', {"name": IMAGE}, timeout=90)
        print(time.strftime('%H:%M:%S'), 'claim%d' % tag, st, b[:140], flush=True)
        if st in (200, 201):
            try:
                dep = json.loads(b).get('deploymentName')
            except Exception:
                dep = None
            if dep:
                found.append(dep)
                stop.set()
                return
        if st == 429:
            time.sleep(10); continue
        if st == 0:
            # transport failure, the POST may still have landed
            got = mine()
            if got:
                found.extend(got); stop.set(); return
        time.sleep(3)


def main():
    deadline = time.time() + int(sys.argv[1] if len(sys.argv) > 1 else 1800)

    already = mine()
    if already:
        found.extend(already); stop.set()
    else:
        ts = [threading.Thread(target=claimer, args=(i,), daemon=True) for i in range(2)]
        for i, t in enumerate(ts):
            t.start(); time.sleep(1.5)
        while not stop.is_set() and time.time() < deadline:
            got = mine()
            if got:
                found.extend(got); stop.set(); break
            time.sleep(3)

    stop.set()
    time.sleep(2)
    names = sorted(set(found) | set(mine() or []))
    if not names:
        print('never got a slot'); return 1
    dep = names[0]
    for extra in names[1:]:
        print('releasing spare slot', extra, flush=True)
        release(extra)

    host, port = dep + '.challs.ctf.thefewchosen.com', 1337
    print('TARGET', host, port, flush=True)

    flag = None
    for attempt in range(60):
        if time.time() > deadline:
            break
        try:
            out = sb.run(host, port)
            m = re.search(rb'TFCCTF\{[^}]*\}', out)
            if m:
                flag = m.group(0).decode(); break
        except Exception as e:
            print('attempt', attempt, 'failed', repr(e), flush=True)
        time.sleep(2)

    if flag:
        print('GOT FLAG', flag, flush=True)
        open(os.path.join(HERE, '..', 'artifacts', 'FLAG.txt'), 'w').write(flag + '\n')
        release(dep)          # hand the slot straight back to the queue
        return 0
    print('no flag', flush=True)
    release(dep)
    return 1


if __name__ == '__main__':
    sys.exit(main())
