#!/usr/bin/env python3
"""
Proxy-side facts about /random_ahh_game and the CHEAT method.

Does NOT drive the game (that's the backend agent's joint). It establishes
only what proxoxy does with that path, those methods, and a JSON body.
"""
import socket, sys, time, json

def conv(host, port, msgs, wait=0.5):
    """Send several requests on ONE keep-alive connection, return the replies."""
    out = []
    s = socket.create_connection((host, int(port)), timeout=8)
    try:
        for m in msgs:
            s.sendall(m); time.sleep(wait); s.settimeout(1.3)
            o = b""
            try:
                while True:
                    d = s.recv(65536)
                    if not d: break
                    o += d
            except socket.timeout:
                pass
            out.append(o)
    finally:
        try: s.close()
        except Exception: pass
    return out

def r(method, path=b"/random_ahh_game", body=b"", ct=None, chunked=False):
    h = method + b" " + path + b" HTTP/1.1\r\nHost: h\r\n"
    if ct: h += b"Content-Type: " + ct + b"\r\n"
    if chunked:
        return h + b"Transfer-Encoding: chunked\r\n\r\n" + (b"%x\r\n" % len(body)) + body + b"\r\n0\r\n\r\n"
    return h + b"Content-Length: %d\r\n\r\n" % len(body) + body

def show(tag, o):
    if not o:
        print("  %-34s CLOSED / zero bytes" % tag); return
    status = o.split(b"\r\n")[0].decode("latin-1")
    body = o.split(b"\r\n\r\n", 1)[-1][:96].decode("latin-1").replace("\n", " ")
    print("  %-34s %-32s %s" % (tag, status, body))

def main():
    host, port = sys.argv[1], sys.argv[2]
    J = json.dumps({"cheat_number": 5}).encode()
    print("== does proxoxy forward each game method at all? ==")
    seq = [r(m) for m in (b"GET", b"PLAY", b"RESET", b"STOP", b"CHEAT", b"FLAG", b"BOGUS")]
    for m, o in zip((b"GET", b"PLAY", b"RESET", b"STOP", b"CHEAT", b"FLAG", b"BOGUS"),
                    conv(host, port, seq)):
        show(m.decode(), o)
    print("== CHEAT with a real JSON body (reset, play, cheat) ==")
    seq = [r(b"RESET"), r(b"PLAY"), r(b"CHEAT", body=J, ct=b"application/json")]
    for t, o in zip(("RESET", "PLAY", "CHEAT json CL"), conv(host, port, seq)):
        show(t, o)
    print("== CHEAT with a CHUNKED JSON body ==")
    seq = [r(b"RESET"), r(b"PLAY"),
           r(b"CHEAT", body=J, ct=b"application/json", chunked=True)]
    for t, o in zip(("RESET", "PLAY", "CHEAT json chunked"), conv(host, port, seq)):
        show(t, o)
    print("== CHEAT with a LARGE JSON body (64 KiB of padding) ==")
    big = json.dumps({"cheat_number": 5, "pad": "A" * 65536}).encode()
    seq = [r(b"RESET"), r(b"PLAY"), r(b"CHEAT", body=big, ct=b"application/json")]
    for t, o in zip(("RESET", "PLAY", "CHEAT json 64KiB"), conv(host, port, seq)):
        show(t, o)
    print("== is the game path blocked by any rule? (no brevski header) ==")
    for p in (b"/random_ahh_game", b"/random_ahh_game?x=1", b"/RANDOM_AHH_GAME"):
        show(p.decode(), conv(host, port, [r(b"PLAY", path=p)])[0])

if __name__ == "__main__":
    main()
