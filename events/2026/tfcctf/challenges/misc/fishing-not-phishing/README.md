# Fishing not Phishing

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | misc |
| Difficulty | baby |
| Author | Walker |
| Points at close | 144 |
| Solves | 105 |
| Status | unsolved |

> Not every vessel leaves a clear trail behind.
>
> Three years ago, during this same month, one vessel departed from port and eventually began fishing somewhere offshore. The information needed to reconstruct that moment is still out there...
>
> Find the following:
>
>  - the vessel's MMSI
>
>  - the port of departure
>
>  - the date when the vessel started fishing
>
>  - the time when the fishing activity started
>
>  - the distance, in kilometers, between the departure port and the location where fishing began
>
> Flag Format
>
> TFCCTF{MMSI_Port Name_DD.MM.YYYY_HH:MM_AM/PM_distance}
>
> The time must be provided in UTC, using the 12-hour format with AM or PM.
>
> The distance must be expressed in kilometers, rounded to one decimal place.
>
> Port Name is in lowercase
>
> Example flag
> TFCCTF{247363350_bari_07.09.2028_09:45_PM_130.7}

Files: [`Fishing.jpeg`](handout/Fishing.jpeg)

<details>
<summary><b>How Far I Got</b></summary>

## What I missed

The bow fragment reads `DE MARE 1`, and completing it to Steaua De Mare 1 names the vessel. After that, Global Fishing Watch gives every field. I never joined the fragment to a Romanian name. [Harshit](https://harshitc.me) sent the working solution after the contest closed, and it's in the second section.

I also took "offshore" from the challenge text as a filter. GFW puts this vessel's first fishing event about 11 km from port, so my offshore filters threw it out.

## Recon

The handout is a 326 by 200 progressive JPEG at quality 50. The `exiftool` dump in `artifacts/handout-Fishing.exif.txt` shows plain JFIF, and binwalk and steghide come up empty. Reverse image search came up empty too, so the source photo isn't indexed. That leaves the event data at [Global Fishing Watch](https://globalfishingwatch.org/our-apis/).

## GFW without a token

The v3 gateway returns 401 `invalid token` to a bare request. It answers in full if you add the two headers its own web map sends:

```bash
curl -s 'https://gateway.api.globalfishingwatch.org/v3/vessels/search?query=MARE' \
  -H 'Origin: https://globalfishingwatch.org' \
  -H 'Referer: https://globalfishingwatch.org/'
```

`/v3/events` worked the same way when I tried it. `/v3/vessels/search` took a SQL-flavored `where` clause such as `where=shipname LIKE '%MARE'`. It capped `limit` at 50 and returned HTTP 422 for any `offset`, so I sharded by flag or by pattern instead of paging. The events endpoint paged fine at `limit=1000`.

## The September sweep

September 2023 holds 1,337,801 fishing events. Keeping each vessel's earliest one gives a table of 86,642 vessels, with start time, name, MMSI, flag, position, and GFW's `startDistanceFromPortKm`. Every later filter ran against that table.

## Dead end: the hull name

Names ending in MARE gave one offshore September fisher, MADONNINA DEL MARE. Its published photo shows an orange Mar del Plata fresquero, not the handout's navy-over-white hull with a yellow A-frame. That query also missed names that only contain the fragment, since `shipname LIKE '%MARE'` anchors at the end.

Other readings failed on photos or tracks. A Japanese `...O MARU` gave 26 offshore boats. The 22 without an IMO are too small for the handout's hull. Two of the other four have photos, and both show kanji bow names. Reading the fragment inside PONOMAREV gave ANATOLIY PONOMAREV, a gray 104 m factory stern trawler without the yellow A-frame. Nordic names fit the glyphs because GFW writes Norwegian `Ø` as `OE` (`BRIMØY` becomes `BRIMOEY`). All three Nordic candidates make a port visit between departure and fishing, at implied transit speeds of 0.4 to 0.9 knots.

A painted name can be years out of date, so I swept registry and former names too. That gave 1,902 identities with MARE, 69 with September 2023 fishing, and 12 offshore. Nine of the 12 fail on photos, and the other three don't have a photo anywhere. Looser patterns around `MAR` gave 101 vessels and 49 photos, and none matched.

STEAUA DE MARE 1 was one of the 69. The sweep printed only vessels whose `startDistanceFromPortKm` is 50 or more, and its value is about 11, so I never looked at it.

## Dead end: brute-forcing the distance

In four screenshots of the event's `#general` channel, players were stuck on the distance and nobody asked about the vessel. One solver said it's easy "if you found correct platform for distance".

Someone confirmed there's no submission limit, so I sent roughly 2,500 submissions over about 1,250 candidate tuples. Each used a great-circle figure or GFW's `startDistanceFromPortKm`, so a right tuple still had to match the author's arithmetic to 100 meters.

`artifacts/shortlist.csv`, `artifacts/profile.csv`, `artifacts/flag_candidates.csv`, and `artifacts/final_ranked.csv` are the ranked candidate tables. None of them has the answer.

</details>

<details>
<summary><b>Solution courtesy of <a href="https://harshitc.me" target="_blank">harshitc.me</a></b></summary>

`solve/harshit_method.py` reproduces Harshit's solution, and their own writeup is on [their site](https://harshitc.me).

The vessel is `Steaua De Mare 1`, MMSI `264900119`, Romanian. GFW gives it the vessel id `b1ad0b9ae-e8b6-ee78-9648-cd40b961ce46`, and two event queries supply every other field.

```sh
curl -g --request GET \
  'https://gateway.api.globalfishingwatch.org/v3/events?vessels[0]=b1ad0b9ae-e8b6-ee78-9648-cd40b961ce46&datasets[0]=public-global-port-visits-events:latest&start-date=2023-08-25&end-date=2023-09-30&limit=50&offset=0' \
  -H "Authorization: Bearer $GFW_TOKEN"
```

The port visit has a `startAnchorage` of `rou-constanta` at `44.11006002570753, 28.738262100497092`. The first fishing event starts at `2023-09-21T07:17:06Z` at `44.0637, 28.9227`.

The fishing event's `startDistanceFromPortKm` is `10.95487`, but GFW measures that to the nearest anchorage. The flag uses the departure anchorage, with a plain haversine:

```python
def haversine(lat1, lon1, lat2, lon2):
    R = 6371.0088  # IUGG mean Earth radius, km
    phi1, phi2 = radians(lat1), radians(lat2)
    dphi, dlambda = radians(lat2 - lat1), radians(lon2 - lon1)
    a = sin(dphi/2)**2 + cos(phi1)*cos(phi2)*sin(dlambda/2)**2
    return R * 2 * atan2(sqrt(a), sqrt(1-a))
```

That gives `15.606954`, so `15.6`. "Found correct platform for distance" meant GFW's coordinates with your own haversine.

## Why my pairing dropped it

The port visit ends at `2023-09-21T08:44:57Z`, an hour and a half after fishing starts at `2023-09-21T07:17:06Z`. My pipeline wanted a transit of at least four hours at six knots or more, so this negative gap failed at the pairing stage. Those two floors also imply at least `4 h x 6 kn x 1.852 km/nm = 44.4 km`, and the answer is 15.6 km.

Flag: `TFCCTF{264900119_constanta_21.09.2023_07:17_AM_15.6}`

## Reproduce

```bash
python3 solve/harshit_method.py            # recompute the flag from the recorded events
GFW_TOKEN=... python3 solve/harshit_method.py --live    # re-fetch from the live API
FNP_MMSI=264900119 python3 solve/solve.py  # derive four fields from any MMSI
```

`solve/solve.py` is my own driver. Given one MMSI, it takes the first September 2023 fishing event and the latest port visit that ends before it. It prints the distance as a spherical haversine, a WGS84 Vincenty geodesic, and GFW's own field. The Constanta visit ends after fishing starts, so the driver doesn't pick it as the departure.

</details>
