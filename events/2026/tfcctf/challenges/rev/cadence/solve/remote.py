#!/usr/bin/env python3
"""
Connect to the cadence encore service over TLS, read the session nonce,
solve the resonance system and submit the base64 WAV.
"""
import base64, re, socket, ssl, sys, time
_CH = __import__("os").path.dirname(__import__("os").path.dirname(__import__("os").path.abspath(__file__)))

sys.path.insert(0, f"{_CH}/solve")
import cadence as C

HOST = sys.argv[1]
PORT = int(sys.argv[2]) if len(sys.argv) > 2 else 1337

ctx = ssl.create_default_context()
ctx.check_hostname = False
ctx.verify_mode = ssl.CERT_NONE

raw = socket.create_connection((HOST, PORT), timeout=30)
s = ctx.wrap_socket(raw, server_hostname=HOST)
s.settimeout(0.4)

allbuf = bytearray()
buf = bytearray()


def pump(t=3.0):
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
        buf.extend(d)
        allbuf.extend(d)


def clean(b):
    txt = bytes(b).decode("utf-8", "replace")
    txt = re.sub(r"\x1b\[[0-9;?]*[A-Za-z]", "\n", txt)
    txt = re.sub(r"\x1b\][^\x07]*\x07", "", txt)
    return "\n".join(l.strip() for l in txt.split("\n") if l.strip())


def flat(b):
    t = bytes(b).decode("utf-8", "replace")
    t = re.sub(r"\x1b\[[0-9;?]*[A-Za-z]", "", t)
    t = re.sub(r"\x1b\][^\x07]*\x07", "", t)
    return t.replace("\r", "").replace("\n", "")


def find_nonce():
    for src in (flat(allbuf), clean(allbuf)):
        mm = re.findall(r"(?<![0-9a-f])[0-9a-f]{32}(?![0-9a-f])", src)
        if mm:
            return mm
    return []


m = []
for k in range(20):
    pump(2.0)
    m = find_nonce()
    if m:
        break
if not m:
    print(clean(allbuf)[:2500])
    sys.exit("no nonce")
nonce = bytes.fromhex(m[-1])
rate = C.RATES[nonce[0] % 6]
print("nonce", nonce.hex(), "rate", rate, flush=True)

smp = C.solve_auto(nonce, rate)
b64 = base64.standard_b64encode(C.make_wav(smp, rate)).decode()
print("b64 len", len(b64), flush=True)

for ch in b64:
    s.sendall(ch.encode())
    time.sleep(0.012)
buf.clear()
pump(2.5)
counts = re.findall(r"\[(\d+) chars\]", clean(buf))
print("char counter says", counts[-3:] if counts else None, flush=True)

buf.clear()
s.sendall(b"\r")
pump(8.0)
scr = clean(buf)
print("=== after submit ===")
print(scr[-4000:])
txt = bytes(allbuf).decode("utf-8", "replace")
txt = re.sub(r"\x1b\[[0-9;?]*[A-Za-z]", "", txt)
txt = re.sub(r"\x1b\][^\x07]*\x07", "", txt)
txt = txt.replace("\r", "").replace("\n", "")
for pat in ("PERFECT CADENCE", "Dissonance", "Wrong sample rate", "Too few samples",
            "Not a mono", "not valid base64"):
    if pat in txt:
        print("SAW:", pat)
flags = set(re.findall(r"TFCCTF\{[^}\s]*\}", txt))
for f in flags:
    print("FLAG:", f)
open(f"{_CH}/scratch/remote_raw.bin", "wb").write(bytes(allbuf))
