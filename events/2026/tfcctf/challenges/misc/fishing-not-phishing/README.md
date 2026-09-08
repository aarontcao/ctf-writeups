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

I'm usually ok at OSINT but I just wasn't able to get this one. Details I could make out from the photo:
- stern trawler
- knuckle-boom crane forward of the bridge
- gantry aft with a pale drum, both
- navy blue hull
- white topsides
- bow to the left, so the surviving name fragment is the end of the name

Reverse image search on TinEye, Yandex, Bing, Google, didn't give me anything (but tbh I didn't spend very long on it). I tried a template matcher on the hull name, first with MARE and then with variations like MAAE, MRRE, MARB, and that didn't work either. The fragment actually did read `DE MARE 1`, but I never joined that up to `Steaua De Mare 1` lol.

So then I hit up [Global Fishing Watch](https://globalfishingwatch.org/our-apis/) and pulled every port-visit-then-fishing pair in September 2023 and tried to filter down to the answer. That gave me 6219 candidate rows.

For distance I computed every combination of spherical haversine and WGS84 geodesic and found only 2 of 401 rows agreeing to one decimal under two readings. So then I tried bruteforcing, but it was already pretty late by then so I gave up and went to bed.
</details>

<details>
<summary><b>Solution courtesy of <a href="https://harshitc.me" target="_blank">harshitc.me</a></b></summary>

[Harshit](https://harshitc.me) sent me their solution after the contest ended; see `solve/harshit_method.py` for a reproduction. We present it here for archival purposes (but also check out their website and blog for their full writeup).

The vessel was actually `Steaua De Mare 1`, MMSI `264900119`. If you're not silly like me, you can read `DE MARE 1` off the hull and trace the full name from that. Then, hit up GFW as before and pull the events you need straight from the [v3 API](https://globalfishingwatch.org/our-apis/). You can get the internal vessel id `b1ad0b9ae-e8b6-ee78-9648-cd40b961ce46` from the API as well:

```sh
curl -g --request GET \
  'https://gateway.api.globalfishingwatch.org/v3/events?vessels[0]=b1ad0b9ae-e8b6-ee78-9648-cd40b961ce46&datasets[0]=public-global-port-visits-events:latest&start-date=2023-08-25&end-date=2023-09-30&limit=50&offset=0' \
  -H "Authorization: Bearer $GFW_TOKEN"
```

There are only two relevant events. The port visit gives the departure anchorage `rou-constanta` at `44.11006002570753, 28.738262100497092`, and the first fishing event gives `2023-09-21T07:17:06Z` at `44.0637, 28.9227`.

The distance is a trap though. GFW gives you a `startDistanceFromPortKm` on the fishing event (`10.95487`), but that isn't the number the flag wants. Take the great-circle distance from the anchorage to the fishing position instead:

```python
def haversine(lat1, lon1, lat2, lon2):
    R = 6371.0088  # mean Earth radius, km
    phi1, phi2 = radians(lat1), radians(lat2)
    dphi, dlambda = radians(lat2 - lat1), radians(lon2 - lon1)
    a = sin(dphi/2)**2 + cos(phi1)*cos(phi2)*sin(dlambda/2)**2
    return R * 2 * atan2(sqrt(a), sqrt(1-a))
```

That gives `15.606954`, so `15.6`.

Flag: `TFCCTF{264900119_constanta_21.09.2023_07:17_AM_15.6}`
</details>
