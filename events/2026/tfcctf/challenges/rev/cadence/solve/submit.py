#!/usr/bin/env python3
"""
Connect, wait for the encore panel, type a precomputed base64 WAV, submit.
"""
import re, socket, ssl, sys, time
_CH = __import__("os").path.dirname(__import__("os").path.dirname(__import__("os").path.abspath(__file__)))

HOST = sys.argv[1]
PORT = int(sys.argv[2]) if len(sys.argv) > 2 else 1337
B64 = open(sys.argv[3]).read().strip() if len(sys.argv) > 3 else None
DELAY = float(sys.argv[4]) if len(sys.argv) > 4 else 0.03

ctx = ssl.create_default_context()
ctx.check_hostname = False
ctx.verify_mode = ssl.CERT_NONE
s = ctx.wrap_socket(socket.create_connection((HOST, PORT), timeout=30), server_hostname=HOST)
s.settimeout(0.3)

allbuf = bytearray()


def pump(t):
    end = time.time() + t
    while time.time() < end:
        try:
            d = s.recv(65536)
        except (socket.timeout, ssl.SSLWantReadError):
            continue
        except OSError:
            break
        if not d:
            break
        allbuf.extend(d)


def flat(b=None):
    t = bytes(allbuf if b is None else b).decode("utf-8", "replace")
    t = re.sub(r"\x1b\[[0-9;?]*[A-Za-z]", "", t)
    t = re.sub(r"\x1b\][^\x07]*\x07", "", t)
    return t.replace("\r", "").replace("\n", "")


def dump(tag):
    t = flat()
    print("---", tag, "len", len(t))
    for pat in ("PERFECT CADENCE", "Dissonance", "Wrong sample rate", "Too few samples",
                "Not a mono", "not valid base64", "TFCCTF"):
        if pat in t:
            print("   SAW:", pat)
    for f in set(re.findall(r"TFCCTF\{[^}]{0,120}\}", t)):
        print("   FLAG:", f)
    cs = re.findall(r"\[\s*(\d+) chars\]", t)
    print("   counters", cs[-4:])


for _ in range(75):
    pump(2.0)
    if _ % 10 == 0:
        print("wait", _*2, "s, bytes", len(allbuf), flush=True)
    if re.search(r"(?<![0-9a-f])[0-9a-f]{32}(?![0-9a-f])", flat()):
        break
n = re.findall(r"(?<![0-9a-f])[0-9a-f]{32}(?![0-9a-f])", flat())
print("nonce", n[-1] if n else None, flush=True)
dump("boot")
if not n:
    sys.exit("no nonce")

sys.path.insert(0, f"{_CH}/solve")
import base64 as _b64
import cadence as C
_nonce = bytes.fromhex(n[-1])
_rate = C.RATES[_nonce[0] % 6]
B64 = _b64.standard_b64encode(C.make_wav(C.solve_auto(_nonce, _rate), _rate)).decode()
print("rate", _rate, "b64 len", len(B64), flush=True)

mark = len(allbuf)
for ch in B64:
    s.sendall(ch.encode())
    time.sleep(DELAY)
pump(3.0)
dump("typed")

s.sendall(b"\r")
pump(10.0)
dump("submitted")
open(f"{_CH}/scratch/submit_raw.bin", "wb").write(bytes(allbuf))
print(flat()[-1200:])
