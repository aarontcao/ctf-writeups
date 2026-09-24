#!/usr/bin/env python3
"""
Ground truth for the auth0-spa-js localStorage cache shape on this tenant.

Guessing the cache key twice has cost two runs, so log in through the real
universal login once and read the format off a live browser.

NEVER prints the access token or the id token. Only key names, field names and
value lengths, because this output goes into the ledger.

Run: $HOME/ctf-tools/venv/bin/python authdump.py
"""

import json
import os
import re
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

import ari

CHROME = os.path.expanduser("~/ctf-tools/chrome/chrome")
APP = "https://ariadnetab.xyz"
SECRET_FIELDS = {"access_token", "id_token", "refresh_token"}


def redact(value, depth=0):
    """Structure only. Any string that could be a credential becomes <len N>."""
    if isinstance(value, dict):
        return {k: ("<%s len %d>" % (k, len(str(v))) if k in SECRET_FIELDS
                    else redact(v, depth + 1)) for k, v in value.items()}
    if isinstance(value, list):
        return [redact(v, depth + 1) for v in value]
    if isinstance(value, str) and len(value) > 60:
        return "<str len %d>" % len(value)
    return value


def wait_for(page, predicate, timeout=90):
    end = time.time() + timeout
    while time.time() < end:
        if predicate():
            return True
        page.wait_for_timeout(500)
    return False


def main():
    state = ari.load_state()
    email, password = state["email"], state["password"]

    from playwright.sync_api import sync_playwright

    with sync_playwright() as pw:
        browser = pw.chromium.launch(executable_path=CHROME, headless=True,
                                     args=["--no-sandbox", "--disable-dev-shm-usage"])
        page = browser.new_context().new_page()

        # A fresh profile can't log in through the web UI at all. start() awaits
        # encodedDeviceKeys() first, and with no stored keypair and no native
        # port loadEncodedKeys() rethrows the 8 s timeout, so accessToken() never
        # runs and #login stays hidden. The keypair has to be planted before the
        # app is usable, so the bot's phone was bootstrapped through
        # OpenDocumentActivity.
        import docs
        keys = docs.ensure_keys(state)
        print("[*] planting a device keypair so the app can boot at all")
        page.goto(APP + "/", wait_until="domcontentloaded")
        page.evaluate(
            "([priv, pub]) => { localStorage.setItem('rsaPrivateKeyPkcs8', priv);"
            " localStorage.setItem('rsaPublicKeySpki', pub); }",
            [keys["privateKey"], keys["publicKey"]],
        )

        print("[*] loading the app and clicking sign in")
        page.goto(APP + "/", wait_until="domcontentloaded")
        page.wait_for_selector("#login:not([hidden])", timeout=40000)
        page.click("#login")

        if not wait_for(page, lambda: "auth0.com" in page.url):
            raise SystemExit("never reached auth0, url=%s" % page.url)
        print("[*] at auth0: %s" % page.url.split("?")[0])

        page.wait_for_selector("input#username", timeout=40000)
        page.fill("input#username", email)
        if page.query_selector("input#password"):
            page.fill("input#password", password)
            page.press("input#password", "Enter")
        else:
            page.press("input#username", "Enter")
            page.wait_for_selector("input#password", timeout=40000)
            page.fill("input#password", password)
            page.press("input#password", "Enter")

        # poll instead of expect_navigation, the app may already have landed by
        # the time we start waiting, which is what timed out in payval.
        if not wait_for(page, lambda: page.url.startswith(APP), timeout=120):
            print("    stuck at %s" % page.url[:160])
            try:
                print("    body: %s" % page.inner_text("body")[:400])
            except Exception:
                pass
            raise SystemExit("login did not return to the app")
        print("[*] back at the app: %s" % page.url[:80])

        # Let app.js finish handleRedirectCallback and populate the cache.
        wait_for(page, lambda: page.evaluate(
            "() => Object.keys(localStorage).some(k => k.startsWith('@@auth0spajs@@'))"),
            timeout=60)
        page.wait_for_timeout(3000)

        dump = page.evaluate("""() => {
          const out = {};
          for (const k of Object.keys(localStorage)) {
            const raw = localStorage.getItem(k);
            try { out[k] = JSON.parse(raw); } catch (e) { out[k] = '<raw len ' + raw.length + '>'; }
          }
          return out;
        }""")

        print("\n===== localStorage on %s after a real login =====" % APP)
        for key in sorted(dump):
            print("\nKEY  %s" % key)
            print("VAL  %s" % json.dumps(redact(dump[key]), indent=2)[:1400])
        browser.close()


if __name__ == "__main__":
    main()
