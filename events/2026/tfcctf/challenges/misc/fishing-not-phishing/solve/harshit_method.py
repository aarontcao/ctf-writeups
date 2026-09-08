#!/usr/bin/env python3
"""
Fishing not Phishing, solved by Harshit (https://harshitc.me).
This file is just for reproduction/archiving.

Run with no arguments, it recomputes the flag from the recorded response.
Give it a token in GFW_TOKEN, it re-fetches the events from the live API.
```
harshit_method.py
GFW_TOKEN=... harshit_method.py --live
```
"""

import argparse
import datetime
import json
import math
import os
import sys
import urllib.error
import urllib.request

GFW = "https://gateway.api.globalfishingwatch.org"
VESSEL_NAME = "Steaua De Mare 1"
VESSEL_ID = "b1ad0b9ae-e8b6-ee78-9648-cd40b961ce46"
MMSI = "264900119"

# The two events, exactly as the v3 API returned them. Kept here so the flag
# is reproducible without a GFW account, since the API needs a personal token.
RECORDED = {
    "port_visit": {
        "start": "2023-07-18T08:28:44.000Z",
        "end": "2023-09-21T08:44:57.000Z",
        "port_visit": {
            "startAnchorage": {
                "id": "rou-constanta",
                "lat": 44.11006002570753,
                "lon": 28.738262100497092,
                "topDestination": "CONSTANTA",
            }
        },
    },
    "first_fishing": {
        "start": "2023-09-21T07:17:06.000Z",
        "position": {"lat": 44.0637, "lon": 28.9227},
        "distances": {"startDistanceFromPortKm": 10.95487},
    },
}


def haversine(lat1, lon1, lat2, lon2, radius=6371.0088):
    """Great-circle distance in km. 6371.0088 is the IUGG mean Earth radius."""
    phi1, phi2 = math.radians(lat1), math.radians(lat2)
    dphi = math.radians(lat2 - lat1)
    dlambda = math.radians(lon2 - lon1)
    a = math.sin(dphi / 2) ** 2 + math.cos(phi1) * math.cos(phi2) * math.sin(dlambda / 2) ** 2
    return radius * 2 * math.atan2(math.sqrt(a), math.sqrt(1 - a))


def fetch(dataset, token):
    url = (f"{GFW}/v3/events?vessels[0]={VESSEL_ID}&datasets[0]={dataset}"
           "&start-date=2023-08-25&end-date=2023-09-30&limit=50&offset=0")
    req = urllib.request.Request(url, headers={"Authorization": f"Bearer {token}"})
    with urllib.request.urlopen(req, timeout=60) as r:
        return json.load(r)["entries"]


def live_events(token):
    visits = fetch("public-global-port-visits-events:latest", token)
    fishing = fetch("public-global-fishing-events:latest", token)
    # the departure is the visit whose end is the last moment in port before
    # fishing starts, and the flag wants the first fishing event after it
    first = min(fishing, key=lambda e: e["start"])
    visit = max((v for v in visits if v["end"] <= first["end"]), key=lambda v: v["end"])
    return {"port_visit": visit, "first_fishing": first}


def build(events):
    anchorage = events["port_visit"]["port_visit"]["startAnchorage"]
    fish = events["first_fishing"]
    km = haversine(anchorage["lat"], anchorage["lon"],
                   fish["position"]["lat"], fish["position"]["lon"])
    when = datetime.datetime.fromisoformat(fish["start"].replace("Z", "+00:00"))
    port = anchorage["topDestination"].lower()
    stamp = when.strftime("%d.%m.%Y_%I:%M_%p")
    return f"TFCCTF{{{MMSI}_{port}_{stamp}_{km:.1f}}}", km, fish


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--live", action="store_true",
                    help="re-fetch from the GFW API, needs GFW_TOKEN")
    a = ap.parse_args()

    if a.live:
        token = os.environ.get("GFW_TOKEN")
        if not token:
            sys.exit("set GFW_TOKEN to a Global Fishing Watch API token")
        try:
            events = live_events(token)
        except urllib.error.HTTPError as e:
            sys.exit(f"GFW API returned {e.code}")
    else:
        events = RECORDED

    flag, km, fish = build(events)
    print(f"vessel     {VESSEL_NAME}  mmsi {MMSI}")
    print(f"port       constanta  (rou-constanta)")
    print(f"fishing    {fish['start']}  at {fish['position']['lat']}, {fish['position']['lon']}")
    print(f"haversine  {km:.6f} km  -> {km:.1f}")
    print(f"GFW field  {fish['distances']['startDistanceFromPortKm']} km  -> "
          f"{fish['distances']['startDistanceFromPortKm']:.1f}   (wrong, do not use)")
    print(f"flag       {flag}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
