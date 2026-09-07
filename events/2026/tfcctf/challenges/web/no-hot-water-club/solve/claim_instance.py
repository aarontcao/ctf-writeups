#!/usr/bin/env python3
"""
Poll the challenge manager for a free isolated slot and claim one.

The team cap is 3 concurrent instances and other agents keep taking the freed
slot, so poll tight. The access token lives 600 s, so re-check expiry on every
iteration through ctf.py.
"""
import importlib.util, json, os, sys, time
import urllib.request

spec = importlib.util.spec_from_file_location("ctfmod", os.path.expanduser("~/.claude/scripts/ctf.py"))
ctfmod = importlib.util.module_from_spec(spec)
spec.loader.exec_module(ctfmod)

MGR = "https://challenge-manager.management.ctf.thefewchosen.com/isolated"
IMAGE = "no-hot-water-team"
OUT = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                   "scratch", "instance.json")


def token():
    if ctfmod.token_expiring(120):
        ok = ctfmod.refresh_access()
        if not ok:
            ctfmod.relogin_quietly()
    return ctfmod.load_token()


def call(method, body=None):
    req = urllib.request.Request(MGR, method=method,
                                 data=json.dumps(body).encode() if body else None)
    req.add_header("Authorization", "Bearer " + (token() or ""))
    req.add_header("content-type", "application/json")
    try:
        with urllib.request.urlopen(req, timeout=20) as r:
            return r.status, r.read().decode()
    except Exception as e:  # noqa: BLE001
        raw = getattr(e, "read", lambda: b"")()
        return getattr(e, "code", -1), (raw.decode(errors="replace") or repr(e))


if __name__ == "__main__":
    limit = int(sys.argv[1]) if len(sys.argv) > 1 else 4000
    for i in range(limit):
        status, text = call("POST", {"name": IMAGE})
        if status == 200 and '"error"' not in text:
            open(OUT, "w").write(text)
            print(time.strftime("%FT%TZ", time.gmtime()), "CLAIMED", text[:400], flush=True)
            sys.exit(0)
        if i % 20 == 0:
            print(time.strftime("%FT%TZ", time.gmtime()), status, text[:120], flush=True)
            _, listing = call("GET")
            print("   listing:", listing[:300], flush=True)
        time.sleep(2)
    sys.exit(1)
