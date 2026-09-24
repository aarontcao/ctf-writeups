#!/usr/bin/env python3
import json, os, sys, urllib.request, urllib.error
T = os.environ.get("CTF_TARGET","http://fluxion-3b475c36f93829ad.challs.ctf.thefewchosen.com").rstrip("/")
def raw(path, data=None, ct="application/json", method=None, timeout=20, headers=None):
    if isinstance(data,str): data=data.encode()
    h={"content-type":ct}
    if headers: h.update(headers)
    req=urllib.request.Request(T+path, data=data, headers=h, method=method or ("POST" if data is not None else "GET"))
    try:
        r=urllib.request.urlopen(req,timeout=timeout); return r.status, r.read()
    except urllib.error.HTTPError as e: return e.code, e.read()
def rpc(method, params=None, timeout=20):
    s,b = raw("/api/rpc", json.dumps({"method":method,"params":params or {}}), timeout=timeout)
    try: return json.loads(b)
    except Exception: return {"_status":s,"_raw":b[:800].decode('utf-8','replace')}
if __name__=="__main__":
    print(json.dumps(rpc(sys.argv[1], json.loads(sys.argv[2]) if len(sys.argv)>2 else {}), indent=1)[:4000])
