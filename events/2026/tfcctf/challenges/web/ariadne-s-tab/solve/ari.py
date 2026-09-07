#!/usr/bin/env python3
"""
ari: client for the Ariadne's Tab web backend and its Auth0 tenant.

Signs up a database user, gets an access token through the cross-origin
authentication flow plus authorization_code + PKCE, then drives the document
API the same way the SPA does.
"""

import base64
import hashlib
import http.cookiejar
import json
import os
import secrets
import sys
import urllib.error
import urllib.parse
import urllib.request

AUTH0 = "https://ariadnetab.eu.auth0.com"
CLIENT_ID = "BlPwCjiomX8gHhIXXGACAIMdcdIrFrQk"
AUDIENCE = "https://ariadnetab.xyz"
APP = "https://ariadnetab.xyz"
CONTENT = "https://content.ariadnetab.xyz"
REALM = "Username-Password-Authentication"
UA = (
    "Mozilla/5.0 (Linux; Android 14; Pixel 7) AppleWebKit/537.36 (KHTML, like Gecko) "
    "Chrome/128.0.0.0 Mobile Safari/537.36"
)
STATE_FILE = os.path.join(os.path.dirname(os.path.abspath(__file__)), ".ari-state.json")

jar = http.cookiejar.CookieJar()
opener = urllib.request.build_opener(urllib.request.HTTPCookieProcessor(jar))


def b64u(raw):
    return base64.urlsafe_b64encode(raw).rstrip(b"=").decode()


def request(url, method="GET", data=None, headers=None, allow_redirect=True):
    body = None
    hdrs = {"User-Agent": UA, "Accept": "application/json, text/plain, */*"}
    if isinstance(data, dict):
        body = json.dumps(data).encode()
        hdrs["Content-Type"] = "application/json"
    elif isinstance(data, bytes):
        body = data
    hdrs.update(headers or {})
    req = urllib.request.Request(url, data=body, method=method, headers=hdrs)
    use = opener
    if not allow_redirect:
        class NoRedirect(urllib.request.HTTPRedirectHandler):
            def redirect_request(self, *a, **k):
                return None
        use = urllib.request.build_opener(
            urllib.request.HTTPCookieProcessor(jar), NoRedirect
        )
    try:
        with use.open(req, timeout=60) as resp:
            return resp.status, dict(resp.headers), resp.read()
    except urllib.error.HTTPError as exc:
        return exc.code, dict(exc.headers), exc.read()


def signup(email, password):
    status, _, raw = request(
        f"{AUTH0}/dbconnections/signup",
        "POST",
        {
            "client_id": CLIENT_ID,
            "email": email,
            "password": password,
            "connection": REALM,
        },
        {"Origin": APP, "Referer": APP + "/"},
    )
    return status, raw.decode("utf-8", "replace")


def _forms(html):
    """Very small HTML form scraper: returns [(action, method, {name: value})]."""
    import re

    out = []
    for match in re.finditer(r"<form\b([^>]*)>(.*?)</form>", html, re.S | re.I):
        attrs, inner = match.group(1), match.group(2)
        action = re.search(r'action\s*=\s*"([^"]*)"', attrs, re.I)
        method = re.search(r'method\s*=\s*"([^"]*)"', attrs, re.I)
        fields = {}
        for inp in re.finditer(r"<input\b([^>]*)>", inner, re.I):
            iattrs = inp.group(1)
            name = re.search(r'name\s*=\s*"([^"]*)"', iattrs, re.I)
            value = re.search(r'value\s*=\s*"([^"]*)"', iattrs, re.I)
            if name:
                fields[name.group(1)] = value.group(1) if value else ""
        out.append((action.group(1) if action else "", (method.group(1) if method else "get").lower(), fields))
    return out


def _universal_login(url, email, password, verbose=False):
    """Walk the Auth0 Universal Login flow starting at an /authorize URL."""
    import html as htmlmod

    for step in range(20):
        status, headers, raw = request(url, headers={"Referer": AUTH0 + "/"}, allow_redirect=False)
        loc = headers.get("Location") or headers.get("location")
        if status in (301, 302, 303, 307) and loc:
            url = urllib.parse.urljoin(url, loc)
            params = urllib.parse.parse_qs(urllib.parse.urlparse(url).query)
            if "code" in params:
                return params["code"][0]
            if url.startswith(APP):
                raise SystemExit(f"redirected to app without code: {url}")
            continue
        page = raw.decode("utf-8", "replace")
        forms = _forms(page)
        if not forms:
            raise SystemExit(f"no form at {url} (status {status}): {page[:600]}")
        action, method, fields = forms[0]
        if "username" in fields or "email" in fields:
            fields["username" if "username" in fields else "email"] = email
        if "password" in fields:
            fields["password"] = password
        elif "username" not in fields and "email" not in fields:
            raise SystemExit(f"unexpected form at {url}: {fields}")
        fields.setdefault("action", "default")
        fields = {k: htmlmod.unescape(v) for k, v in fields.items()}
        post_url = urllib.parse.urljoin(url, htmlmod.unescape(action)) if action else url
        if verbose:
            print("form ->", post_url, sorted(fields))
        status, headers, raw = request(
            post_url,
            "POST",
            urllib.parse.urlencode(fields).encode(),
            {"Content-Type": "application/x-www-form-urlencoded", "Origin": AUTH0, "Referer": url},
            allow_redirect=False,
        )
        loc = headers.get("Location") or headers.get("location")
        if status in (301, 302, 303, 307) and loc:
            url = urllib.parse.urljoin(post_url, loc)
            params = urllib.parse.parse_qs(urllib.parse.urlparse(url).query)
            if "code" in params:
                return params["code"][0]
            continue
        page = raw.decode("utf-8", "replace")
        if "password" in page.lower() and status == 200:
            url = post_url
            continue
        raise SystemExit(f"login POST stopped {status}: {page[:600]}")
    raise SystemExit("universal login did not finish")


def get_token(email, password, verbose=False):
    verifier = b64u(secrets.token_bytes(32))
    challenge = b64u(hashlib.sha256(verifier.encode()).digest())
    state = b64u(secrets.token_bytes(16))
    query = urllib.parse.urlencode(
        {
            "client_id": CLIENT_ID,
            "response_type": "code",
            "redirect_uri": APP + "/",
            "scope": "openid profile email",
            "audience": AUDIENCE,
            "state": state,
            "nonce": b64u(secrets.token_bytes(16)),
            "code_challenge": challenge,
            "code_challenge_method": "S256",
        }
    )
    code = _universal_login(f"{AUTH0}/authorize?{query}", email, password, verbose)

    status, _, raw = request(
        f"{AUTH0}/oauth/token",
        "POST",
        urllib.parse.urlencode(
            {
                "grant_type": "authorization_code",
                "client_id": CLIENT_ID,
                "code": code,
                "code_verifier": verifier,
                "redirect_uri": APP + "/",
            }
        ).encode(),
        {"Content-Type": "application/x-www-form-urlencoded", "Origin": APP},
    )
    if status != 200:
        raise SystemExit(f"token failed {status}: {raw[:400]!r}")
    return json.loads(raw)


def api(path, token, body=None, origin=CONTENT):
    status, headers, raw = request(
        f"{APP}/api/{path}",
        "POST",
        body if body is not None else {},
        {"Authorization": f"Bearer {token}", "Origin": origin, "Referer": origin + "/"},
    )
    try:
        return status, json.loads(raw), headers
    except Exception:
        return status, raw.decode("utf-8", "replace"), headers


def load_state():
    if os.path.exists(STATE_FILE):
        with open(STATE_FILE) as handle:
            return json.load(handle)
    return {}


def save_state(state):
    with open(STATE_FILE, "w") as handle:
        json.dump(state, handle, indent=2)


if __name__ == "__main__":
    print(__doc__)
