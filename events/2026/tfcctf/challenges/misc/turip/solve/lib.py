import json, sys, os, urllib.request

API = "https://api.ctf.thefewchosen.com"

def jwt():
    d = json.load(open(os.path.expanduser("~/.config/ctf/token.json")))
    return d["token"]

def api_get(path):
    req = urllib.request.Request(API + path, headers={
        "Authorization": "Bearer " + jwt(),
        "Accept": "application/json",
    })
    with urllib.request.urlopen(req, timeout=20) as r:
        return json.loads(r.read())

def team_token():
    for p in ("/team", "/user/team", "/teams/me"):
        try:
            d = api_get(p)
        except Exception:
            continue
        if isinstance(d, dict) and d.get("invite_token"):
            return d["invite_token"]
    raise SystemExit("no invite token")
