import json, sys, urllib.request, urllib.error
import os
CM="https://challenge-manager.management.ctf.thefewchosen.com"
tok=json.load(open(os.path.expanduser("~/.config/ctf/token.json")))
t = tok.get("token") or tok.get("access_token") or tok.get("jwt")
if not t:
    print("keys:", list(tok.keys())); sys.exit(1)
def req(method, path, body=None):
    data = json.dumps(body).encode() if body is not None else None
    r = urllib.request.Request(CM+path, data=data, method=method,
        headers={"Authorization":"Bearer "+t, "Content-Type":"application/json",
                 "Origin":"https://ctf.thefewchosen.com","Referer":"https://ctf.thefewchosen.com/"})
    try:
        with urllib.request.urlopen(r, timeout=30) as resp:
            return resp.status, resp.read().decode()
    except urllib.error.HTTPError as e:
        return e.code, e.read().decode()
if __name__=="__main__":
    m,p = sys.argv[1], sys.argv[2]
    b = json.loads(sys.argv[3]) if len(sys.argv)>3 else None
    s,o = req(m,p,b); print(s); print(o[:3000])
