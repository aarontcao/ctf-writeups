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

The surviving fragment on the bow reads `DE MARE 1`, and completing that to `Steaua De Mare
1` names the vessel outright, after which every remaining field of the flag is one Global
Fishing Watch query. I read the fragment as ending in MARE and never joined it to a Romanian
name, so this writeup is mostly a record of what an overnight run of the wrong search looks
like and where each branch of it died. The working solution is in the second section, and it
came from [Harshit](https://harshitc.me) after the contest closed.

Every name query I ran was anchored or filtered in a way that could not reach the answer, and the offshore prior I inherited from the challenge text is false for this vessel, whose first fishing event is 15.6 km from the quay.

## Recon, in the order it ran

```bash
exiftool handout/Fishing.jpeg           # JFIF only, no EXIF, no GPS, no comment segment
binwalk handout/Fishing.jpeg            # nothing appended
steghide extract -sf handout/Fishing.jpeg -p ''
identify -verbose handout/Fishing.jpeg  # 326x200, progressive, 5 markers, 12513 bytes
sha256sum handout/Fishing.jpeg          # 5f28c6a7719e6b904d7820e54372e33aa4e636d8721a2d8e0615e9aa54fdf574
```

The image is clean, and a re-fetch from the platform a day later returned the same 12513
bytes with the same digest, so the handout is the original rather than a truncated download.
A 326 by 200 progressive JPEG at quality 50 is the whole of the evidence. The full
`exiftool` dump is preserved in `artifacts/handout-Fishing.exif.txt`.

Reverse image search comes next and returns a clean negative on every engine reachable from
here. TinEye returns 0 matches against a real result page, Yandex returns a lookalike
cluster of generic trawlers with `hasText=false` on its own OCR, Baidu rejects the upload at
the API, Bing ingests the image but walls the result page behind a captcha, and Google Lens
refuses a datacenter address at every entry point tried. The important control here is human
rather than technical, since the same two searches run from a residential connection also
returned zero results, which turns "our egress is blocked" into "the source photograph is not
indexed".

That negative is what pushes the whole challenge onto the event data, and the data source the
task is built around is [Global Fishing Watch](https://globalfishingwatch.org/our-apis/).

## The GFW API answers without a token

The v3 gateway returns 401 `invalid token` to a bare request and a full response to the same
request including the two headers its own web map sends:

```bash
curl -s 'https://gateway.api.globalfishingwatch.org/v3/vessels/search?query=MARE' \
  -H 'Origin: https://globalfishingwatch.org' \
  -H 'Referer: https://globalfishingwatch.org/'
```

No account, registration, or personal token. `/v3/events` behaves the same way, and
`/v3/vessels/search` accepts a SQL-flavored `where` clause such as
`where=shipname LIKE '%MARE'`, and every name hypothesis below was tested through that
clause.

Two API quirks cost time. The search endpoint caps `limit` at 50 and returns HTTP 422 if you
pass `offset` at all, so it has to be sharded by flag or by pattern rather than paged. The
events endpoint does page deeply, at `limit=1000`, which makes a full-month sweep feasible.

## The sweep that should have answered everything

September 2023 holds 1,337,801 fishing events worldwide, which is 1,338 chunks of a thousand.
Sweeping all of them and keeping each vessel's earliest event produces one table that answers
any later filter requiring zero further API calls, and that table came out at 86,642 vessels, 80,399
of them named, each row holding start time, name, MMSI, flag, position, and GFW's own
`startDistanceFromPortKm`.

The first attempt at that sweep contained a resumability bug whose fix generalizes, since it
checkpointed the result after every chunk and never checkpointed the offset, so a restart
would have reopened at zero and discarded 80,248 vessels of paid-for work. The rewrite keeps
a second file holding the set of completed chunk indices, loads the previous output as a
seed, and fetches only the gaps.

## Dead end: every reading of the hull name

The fragment is five or six glyphs, cut at the left frame edge, and each reading below was
enumerated to exhaustion.

Reading it as a name ending in MARE gives 345 GFW identities transmitting in September 2023,
15 with a September fishing event, and exactly one offshore, MADONNINA DEL MARE, whose
published photograph is an orange Mar del Plata fresquero and therefore not the navy-over-white
hull with a yellow A-frame in the handout. That query also had a bug: `shipname LIKE '%MARE'` anchors at the end of the name and cannot match a name that merely contains the fragment.

Reading it as a Japanese `...O MARU` gives 26 offshore vessels, all Japanese, of which only
four list an IMO number in the GFW registry. The other 22 are small domestic boats, too
small for the handout's multi-deck hull with a crane, a gantry, and a rigged gangway, and the
two of the four with photographs both show kanji bow names where the handout lettering is
Latin.

Reading `OMARE` as the middle of `pon-OMARE-v` produced ANATOLIY PONOMAREV, which looked
strong for twenty minutes and is a 104 m gray Project-1288 factory stern trawler at
Petropavlovsk lacking a yellow A-frame, a blue-and-white hull, or port
departure before its September fishing, which the challenge text requires.

Reading it as Nordic is more interesting, because GFW transliterates Norwegian `Ø` as `OE`,
so a hull painted `BRIMØY` appears in the data as `BRIMOEY` and the glyph shape fits. All
three Nordic candidates die on the same structural test, since each has an intervening port
visit between the claimed departure and the fishing start, and the implied transit speeds
come out at 0.4 to 0.9 knots.

Registry and former names were then swept, because a painted hull name may be years out of
date, giving 1,902 identities with MARE, 69 with any September 2023 fishing event, and 12
offshore, of which 10 were eliminated on photographs and three lack photographs anywhere.
Finally the whole offshore set was resolved by IMO, 30,505 vessels through bulk `/v3/vessels`
at 100 ids per call in 306 requests, which closes the null-flag gap, the former-name gap, and
the Japanese sharding limit in one file. Widening from MARE to the render pattern of a round
letter, a space, and `MAR` gives 101 vessels and 49 photographs, none of which matches.

Three exhaustive searches returning empty pointed at the premise: the glyphs do not spell something like MAR.

## Dead end: trying to read the pixels harder

Richardson-Lucy deconvolution over the lettering at sigma 4, 6, and 8 and 60 to 100
iterations amplifies JPEG ringing and recovers no letters. Measuring the ink instead of
squinting at it gives a band at rows 92 through 104, twelve pixels tall, and a column profile
with about six glyphs spanning columns 0 through 29 at a pitch near 5 pixels, of which
exactly one, at columns 7 through 13, is legible as a wide two-stroke shape consistent with M,
N, H, U, O, or D. One legible glyph cannot select a vessel out of 86,642.

The small reddish shape at the wheelhouse is not evidence either. At 14x it is a narrow
vertical pennant hanging limp against its staff, not a rectangle, so no national ensign can
be read from it. An earlier behavioral sweep over eleven red-and-white flag states rested on
that misreading and, among other things, excluded Japan.

## Dead end: a photo-matching instrument, validated, and still negative

Rather than trusting a similarity score, the crop hunter was validated against a
reconstruction of what the author did to make the handout, namely crop a region, downscale to
326 by 200, and re-encode as a progressive JPEG at quality 50 with 2x2 subsampling. Four real
ShipSpotting photographs were put through that pipeline, each planted as a fake handout in a
field of 250 other real vessel photographs, and the hunter recovered all four with truth
scores between 0.923 and 0.956, never less than 9.8 standard deviations above the field
maximum.

Run over 5,768 harvested photographs, the all-time maximum is 0.725 against a detection floor
measured at 0.92, with a smooth noise band and no gap. The negatives are real, and the source
photograph is not in anything harvested.

## What the field said: how I misread it

Four screenshots of the event `#general` channel reframed the problem, and every message in
them is about the distance:

    dragos       "how are we supposed to get this distance"
    Kenpar       "one decimal place is so annoying"
    ShadowRoot   "SOLVED THE OSINT"
    ShadowRoot   "that is not difficult if you found correct platform for distance"
    dragos       "so i just spam the closest ones? xd  is there a limit to flag submissions"
    Mcsky23      "no"

Nobody complains about naming the vessel. I treated the distance as brute-forceable,
since a player had confirmed no submission limit, and roughly 2,500 submissions went out over
about 1,250 candidate tuples. Every one of those held one of exactly two distances, a
great-circle figure or GFW's `startDistanceFromPortKm`, so even a correct tuple would have
been rejected unless the arithmetic happened to match the author's tool to 100 meters. The
scorer also caps globally at about 0.28 submissions per second, which makes a wide sweep
arithmetically hopeless before it starts.

`artifacts/shortlist.csv`, `artifacts/profile.csv`, `artifacts/flag_candidates.csv`, and
`artifacts/final_ranked.csv` are the ranked candidate tables. None contains the answer.

</details>

<details>
<summary><b>Solution courtesy of <a href="https://harshitc.me" target="_blank">harshitc.me</a></b></summary>

[Harshit](https://harshitc.me) sent their solution after the contest ended, and
`solve/harshit_method.py` reproduces it. Their own writeup is on their site and is the primary
source for the reading of the photograph.

The vessel is `Steaua De Mare 1`, MMSI `264900119`, Romanian. The hull fragment really does
read `DE MARE 1`, and the `1` at the end is the part that makes the name completable, since
a numbered suffix on a Romanian name narrows the field far faster than the letters do. The
Black Sea should have been a prior from the start, given a Romanian organizing team and an
example flag whose port is Italian rather than Romanian.

With the name, GFW gives the internal vessel id `b1ad0b9ae-e8b6-ee78-9648-cd40b961ce46`, and
two event queries supply every remaining field.

```sh
curl -g --request GET \
  'https://gateway.api.globalfishingwatch.org/v3/events?vessels[0]=b1ad0b9ae-e8b6-ee78-9648-cd40b961ce46&datasets[0]=public-global-port-visits-events:latest&start-date=2023-08-25&end-date=2023-09-30&limit=50&offset=0' \
  -H "Authorization: Bearer $GFW_TOKEN"
```

There are only two relevant events in that window. The port visit includes a `startAnchorage`
of `rou-constanta` at `44.11006002570753, 28.738262100497092`, and the first fishing event
starts at `2023-09-21T07:17:06Z` at `44.0637, 28.9227`.

The distance field is a trap. GFW supplies `startDistanceFromPortKm` on the fishing event as
`10.95487`, which measures to the nearest anchorage and is not what the flag wants. The
number the flag wants is the great-circle distance from the departure anchorage to the
position where fishing began:

```python
def haversine(lat1, lon1, lat2, lon2):
    R = 6371.0088  # IUGG mean Earth radius, km
    phi1, phi2 = radians(lat1), radians(lat2)
    dphi, dlambda = radians(lat2 - lat1), radians(lon2 - lon1)
    a = sin(dphi/2)**2 + cos(phi1)*cos(phi2)*sin(dlambda/2)**2
    return R * 2 * atan2(sqrt(a), sqrt(1-a))
```

That gives `15.606954`, so `15.6`, and "found correct platform for distance" turns out to
mean using GFW's coordinates with your own haversine instead of GFW's own distance column.

## Why the sweep could never have found it

Two numbers in those events explain the whole miss, and both are visible in the recorded
response inside `solve/harshit_method.py`.

The port visit ends at `2023-09-21T08:44:57Z` and fishing starts at `2023-09-21T07:17:06Z`,
so the fishing event begins an hour and a half before the port visit is recorded as over. My
pipeline paired a departure with a fishing start by requiring a positive transit gap of at
least four hours at a speed of at least six knots, and this vessel has a negative gap, so it
was discarded at the pairing stage before any name or photograph was considered.

Those same two floors imply a distance of at least `4 h x 6 kn x 1.852 km/nm = 44.4 km`, and the answer is 15.6 km.

Flag: `TFCCTF{264900119_constanta_21.09.2023_07:17_AM_15.6}`

## Reproduce

```bash
python3 solve/harshit_method.py            # recompute the flag from the recorded events
GFW_TOKEN=... python3 solve/harshit_method.py --live    # re-fetch from the live API
FNP_MMSI=264900119 python3 solve/solve.py  # derive four fields from any MMSI
```

`solve/solve.py` is my own driver, kept because it is the reusable half of the work. Given one
MMSI it pulls the vessel, takes the first September 2023 fishing event for the date, the UTC
time in 12-hour form, and the position, takes the latest port visit ending before it for the
departure anchorage, and prints the distance three ways as a spherical haversine, a WGS84
geodesic through a self-contained Vincenty inverse, and GFW's own field.

</details>
