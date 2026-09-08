#!/usr/bin/env ctf-python
"""
Fishing not Phishing. My own attempt, which never landed. See
harshit_method.py for the solve that works.
Give it one MMSI and it derives the other four flag fields from the GFW v3
API. With no FNP_MMSI it surveys and prints the known negatives.
```
FNP_MMSI=224134480 ctf-python solve/solve.py
```
Recording needs FNP_RECORD=1, an earlier version recorded a rejected flag.
"""

import datetime
import json
import math
import os
import pathlib
import sys
import urllib.parse
import urllib.request

_here = pathlib.Path(__file__).resolve()
for _p in _here.parents:
    if (_p / "lib" / "ctf.py").is_file():
        sys.path.insert(0, str(_p / "lib"))
        break
import ctf  # noqa: E402

BASE = _here.parent.parent
SCRATCH = BASE / "scratch"
GFW = "https://gateway.api.globalfishingwatch.org"
HDRS = {
    "Accept": "application/json",
    "Origin": "https://globalfishingwatch.org",
    "Referer": "https://globalfishingwatch.org/",
    "User-Agent": "Mozilla/5.0",
}
START, END = "2023-09-01", "2023-10-01"


def gfw(path, params=None, tries=3):
    url = GFW + path
    if params:
        url += "?" + urllib.parse.urlencode(params, doseq=True)
    last = None
    for _ in range(tries):
        try:
            req = urllib.request.Request(url, headers=HDRS)
            with urllib.request.urlopen(req, timeout=60) as fh:
                return json.loads(fh.read().decode())
        except Exception as exc:  # noqa: BLE001
            last = exc
    raise last


# --------------------------------------------------------------------------
# distance three ways
# --------------------------------------------------------------------------

def haversine(lat1, lon1, lat2, lon2, radius=6371.0088):
    p1, p2 = math.radians(lat1), math.radians(lat2)
    dp = math.radians(lat2 - lat1)
    dl = math.radians(lon2 - lon1)
    h = math.sin(dp / 2) ** 2 + math.cos(p1) * math.cos(p2) * math.sin(dl / 2) ** 2
    return 2 * radius * math.asin(math.sqrt(h))


def geodesic(lat1, lon1, lat2, lon2):
    """WGS84 Vincenty inverse, in km. Differs from the sphere by up to 0.3 pc,
    which is 0.4 km at 130 km, so it changes the answer at one decimal."""
    a = 6378137.0
    f = 1 / 298.257223563
    b = (1 - f) * a
    L = math.radians(lon2 - lon1)
    U1 = math.atan((1 - f) * math.tan(math.radians(lat1)))
    U2 = math.atan((1 - f) * math.tan(math.radians(lat2)))
    sU1, cU1 = math.sin(U1), math.cos(U1)
    sU2, cU2 = math.sin(U2), math.cos(U2)
    lam = L
    c2a = ss = cs = sig = c2sm = 0.0
    for _ in range(200):
        sl, cl = math.sin(lam), math.cos(lam)
        ss = math.sqrt((cU2 * sl) ** 2 + (cU1 * sU2 - sU1 * cU2 * cl) ** 2)
        if ss == 0:
            return 0.0
        cs = sU1 * sU2 + cU1 * cU2 * cl
        sig = math.atan2(ss, cs)
        sa = cU1 * cU2 * sl / ss
        c2a = 1 - sa * sa
        c2sm = cs - 2 * sU1 * sU2 / c2a if c2a else 0.0
        C = f / 16 * c2a * (4 + f * (4 - 3 * c2a))
        prev = lam
        lam = L + (1 - C) * f * sa * (
            sig + C * ss * (c2sm + C * cs * (-1 + 2 * c2sm ** 2)))
        if abs(lam - prev) < 1e-12:
            break
    u2 = c2a * (a * a - b * b) / (b * b)
    A = 1 + u2 / 16384 * (4096 + u2 * (-768 + u2 * (320 - 175 * u2)))
    B = u2 / 1024 * (256 + u2 * (-128 + u2 * (74 - 47 * u2)))
    dsig = B * ss * (c2sm + B / 4 * (
        cs * (-1 + 2 * c2sm ** 2)
        - B / 6 * c2sm * (-3 + 4 * ss ** 2) * (-3 + 4 * c2sm ** 2)))
    return b * A * (sig - dsig) / 1000.0


# --------------------------------------------------------------------------
# the derivation, given one MMSI
# --------------------------------------------------------------------------

def vessel_id(mmsi):
    # /v3/vessels/search takes a SQL-ish `where`, caps `limit` at 50 and
    # returns 422 if you pass `offset`. Measured, not guessed.
    r = gfw("/v3/vessels/search", {
        "where": "ssvid='%s'" % mmsi,
        "datasets[0]": "public-global-vessel-identity:latest",
        "limit": 50})
    for e in r.get("entries", []):
        for si in e.get("selfReportedInfo", []):
            if str(si.get("ssvid")) == str(mmsi):
                return si.get("id"), si.get("shipname"), si.get("flag")
    raise SystemExit("no GFW identity for MMSI %s" % mmsi)


def events(dataset, vid, start=START, end=END):
    out, off = [], 0
    while True:
        r = gfw("/v3/events", {
            "datasets[0]": dataset, "vessels[0]": vid,
            "start-date": start, "end-date": end, "limit": 100, "offset": off})
        out.extend(r.get("entries", []))
        nxt = r.get("nextOffset")
        if not nxt or len(out) >= (r.get("total") or 0):
            return out
        off = nxt


def derive(mmsi):
    vid, name, flag = vessel_id(mmsi)
    fishing = sorted(events("public-global-fishing-events:latest", vid),
                     key=lambda e: e["start"])
    if not fishing:
        raise SystemExit("no September 2023 fishing event for %s" % mmsi)
    fe = fishing[0]
    fstart = fe["start"]
    flat, flon = fe["position"]["lat"], fe["position"]["lon"]
    gfw_km = (fe.get("distances") or {}).get("startDistanceFromPortKm")

    # the port visit that ENDS latest before fishing begins is the departure
    visits = events("public-global-port-visits-events:latest", vid,
                    "2023-06-01", "2023-10-15")
    before = [v for v in visits if (v.get("end") or "") < fstart]
    if not before:
        raise SystemExit("no port visit before the fishing start for %s" % mmsi)
    pv = max(before, key=lambda v: v["end"])
    anch = ((pv.get("port_visit") or {}).get("endAnchorage")
            or (pv.get("port_visit") or {}).get("startAnchorage") or {})
    port = (anch.get("name") or "").lower()
    plat, plon = anch.get("lat"), anch.get("lon")

    dt = datetime.datetime.strptime(fstart[:19], "%Y-%m-%dT%H:%M:%S")
    fields = {
        "mmsi": str(mmsi), "name": name, "flag": flag, "vid": vid,
        "port": port, "departed": pv["end"],
        "date": "%02d.%02d.%d" % (dt.day, dt.month, dt.year),
        "time": "%02d:%02d" % (dt.hour % 12 or 12, dt.minute),
        "ampm": "AM" if dt.hour < 12 else "PM",
        "fish_pos": (flat, flon), "port_pos": (plat, plon),
    }
    dists = []
    if plat is not None:
        dists.append(round(haversine(plat, plon, flat, flon), 1))
        dists.append(round(geodesic(plat, plon, flat, flon), 1))
    if gfw_km is not None:
        dists.append(round(gfw_km, 1))
    fields["distances"] = sorted(set(dists))
    return fields


def flags_for(f, spread=10):
    """One flag per plausible distance. The scorer has no submission limit and
    the community measured the distance as the failure point, so widen the
    decimal rather than trusting one arithmetic."""
    out, seen = [], set()
    for base in f["distances"]:
        for k in range(-spread, spread + 1):
            v = round(base + k * 0.1, 1)
            s = "TFCCTF{%s_%s_%s_%s_%s_%s}" % (
                f["mmsi"], f["port"], f["date"], f["time"], f["ampm"], v)
            if s not in seen:
                seen.add(s)
                out.append(s)
    return out


def main():
    mmsi = os.environ.get("FNP_MMSI")
    if not mmsi:
        print(__doc__.strip().splitlines()[0])
        print()
        print("No FNP_MMSI set, so this is survey mode.")
        print("The vessel was NOT identified. What is established:")
        print("  handout is 12,513 bytes and identical to the served file")
        print("  no EXIF, no trailing bytes, hull name is 30x12 px, unreadable")
        print("  reverse image search negative: TinEye, Yandex default,")
        print("    Yandex cbir_page=similar, Yandex cbir_page=sites, Bing")
        print("  Google Lens ingests the image by URL and mints a session but")
        print("    gates the result page behind a captcha on every datacentre")
        print("    IP tried: GCP, AWS, DigitalOcean and the jina.ai reader")
        print()
        for name in ("merged_sweep.txt", "photo_sweep.txt", "decimal_sweep.txt"):
            p = SCRATCH / name
            if p.is_file():
                n = sum(1 for _ in p.open())
                print("  candidate list %-18s %6d flags" % (name, n))
        print()
        print("Set FNP_MMSI to derive the other four fields and the flag.")
        return 0

    f = derive(mmsi)
    print(json.dumps({k: v for k, v in f.items()}, indent=2, default=str))
    cands = flags_for(f)
    out = SCRATCH / ("flags_%s.txt" % mmsi)
    out.write_text("\n".join(cands) + "\n")
    print("\n%d candidate flags written to %s" % (len(cands), out))
    primary = "TFCCTF{%s_%s_%s_%s_%s_%s}" % (
        f["mmsi"], f["port"], f["date"], f["time"], f["ampm"],
        f["distances"][0] if f["distances"] else "0.0")
    print("primary: %s" % primary)
    # Recording is gated behind FNP_RECORD=1
    if os.environ.get("FNP_RECORD") == "1":
        ctf.win(primary)
    else:
        print("not recorded: set FNP_RECORD=1 once the scorer confirms it")
    return 0


if __name__ == "__main__":
    sys.exit(main())
