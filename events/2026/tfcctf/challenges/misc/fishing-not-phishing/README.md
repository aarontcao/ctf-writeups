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

I'm usually ok at OSINT but I just wasn't able to get this one. Details I could make out:
- stern trawler
- knuckle-boom crane forward of the bridge
- gantry aft with a pale drum, both
- navy blue hull
- white topsides
- bow to the left, so the surviving name fragment is the end of the name

Reverse image search on TinEye, Yandex, Bing, Google, didn't give me anything (but tbh I didn't spend very long on it). I tried a template matcher on the hull name (first with MARE but then with variations like MAAE, MRRE, MARB, etc.) but that didn't work. So I compiled data on every port-visit event with the fishing event after it (September 2023) from [Global Fishing Watch](https://globalfishingwatch.org/our-apis/) and then tried filtering down. The distance was tricky, Global Fishing Watch publishes `startDistanceFromPortKm`, and I computed every combination of spherical haversine and WGS84 geodesics, but only 2 of 401 rows agreed to one decimal under two readings. So then I tried brute-forcing, but by that time it was already getting late and I wanted to sleep, so I gave up.
</details>
