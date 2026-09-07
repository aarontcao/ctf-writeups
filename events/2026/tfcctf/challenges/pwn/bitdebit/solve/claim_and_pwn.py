#!/usr/bin/env python3
"""
Claim an isolated bitdebit3-chal instance with parallel POSTs, then exploit it.

Shape learned from the tagger agent:
  - 4 parallel claim threads, 6 s socket timeout, so one stalled POST can't
    straddle the moment a slot frees.
  - refresh the access token on every call, it lives 600 s and an expired one
    comes back as HTTP 500 rather than 401.
  - the endpoint is <deploymentName>.challs.ctf.thefewchosen.com:1337 over TLS.
  - NEVER take a flag from anywhere but this exploit's own remote output.
"""
import json, urllib.request, urllib.error, time, sys, re, os, threading

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import importlib.util
spec = importlib.util.spec_from_file_location("sb", os.path.join(HERE, "solve-b.py"))
sb = importlib.util.module_from_spec(spec); spec.loader.exec_module(sb)

sys.path.insert(0, os.path.expanduser("~/.claude/scripts"))
import ctf as ctfcli

HOST = 'https://challenge-manager.management.ctf.thefewchosen.com'
IMAGE = 'bitdebit3-chal'
_tok_lock = threading.Lock()


def get_tok():
    with _tok_lock:
        try:
            if ctfcli.token_expiring(margin=120):
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
        r = urllib.request.urlopen(req, timeout=timeout)
        return r.status, r.read().decode()
    except urllib.error.HTTPError as e:
        return e.code, e.read().decode()
    except Exception as e:
        return 0, str(e)


won = threading.Event()
result = {}
stop = threading.Event()


def claimer(idx):
    backoff = idx * 0.7          # stagger the threads
    while not stop.is_set():
        if backoff:
            time.sleep(backoff)
        # POST routinely takes well over 25 s, so give it room; a client-side
        # timeout does NOT mean the claim failed, the lister will show it.
        st, b = call('/isolated', 'POST', {"name": IMAGE}, timeout=90)
        if st == 0 and 'timed out' in b:
            st2, b2 = call('/isolated', 'GET', timeout=25)
            if st2 == 200 and IMAGE in b2 and not won.is_set():
                m = re.search(r'"name":"(' + IMAGE + r'-[0-9a-f]+)"', b2)
                if m:
                    result['inst'] = {"deploymentName": m.group(1)}
                    print(time.strftime('%H:%M:%S'), 'CLAIMED (via GET recheck)', m.group(1), flush=True)
                    won.set()
                    return
        if st in (200, 201):
            try:
                inst = json.loads(b)
            except Exception:
                inst = {"deploymentName": b}
            if not won.is_set():
                result['inst'] = inst
                print(time.strftime('%H:%M:%S'), 'CLAIMED', b, flush=True)
                won.set()
            return
        if st == 429:
            backoff = min(2.0, (backoff or 0.25) * 2)
        else:
            backoff = 0.5
        if st not in (409, 429):
            print(time.strftime('%H:%M:%S'), 'thread', idx, st, b[:120], flush=True)


def lister():
    while not stop.is_set() and not won.is_set():
        st, b = call('/isolated', 'GET')
        print(time.strftime('%H:%M:%S'), 'list', st, b[:260], flush=True)
        time.sleep(10)


def delete_instance(name):
    for path, method in (('/isolated', 'DELETE'), ('/isolated/' + name, 'DELETE')):
        body = {"name": name} if path == '/isolated' else None
        st, b = call(path, method, body, timeout=15)
        print('delete', path, st, b[:200], flush=True)
        if st in (200, 201, 204):
            return True
    return False


def main():
    deadline = time.time() + int(sys.argv[1] if len(sys.argv) > 1 else 2400)
    threads = [threading.Thread(target=claimer, args=(i,), daemon=True) for i in range(4)]
    threads.append(threading.Thread(target=lister, daemon=True))
    for t in threads:
        t.start()
    while time.time() < deadline and not won.is_set():
        time.sleep(0.2)
    stop.set()
    if not won.is_set():
        print('never claimed a slot'); return 1

    inst = result['inst']
    dep = inst.get('deploymentName') or inst.get('name') or inst.get('data')
    host, port = str(dep) + '.challs.ctf.thefewchosen.com', 1337
    print('TARGET', host, port, flush=True)

    flag = None
    end = time.time() + 170
    attempt = 0
    while time.time() < end and flag is None:
        attempt += 1
        try:
            out = sb.run(host, port)
            m = re.search(rb'TFCCTF\{[^}]*\}', out)
            if m:
                flag = m.group(0).decode()
        except Exception as e:
            print('attempt', attempt, 'failed', repr(e), flush=True)
        if flag is None:
            time.sleep(1.5)

    if flag:
        # Only ever from this exploit's own remote output. No other source.
        print('GOT FLAG', flag, flush=True)
        with open(os.path.join(HERE, '..', 'artifacts', 'FLAG.txt'), 'w') as fh:
            fh.write(flag + '\n')
    else:
        print('no flag', flush=True)
    delete_instance(str(dep))
    return 0 if flag else 1


if __name__ == '__main__':
    sys.exit(main())
