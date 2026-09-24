# Capture the Flag?

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | misc |
| Format | King of the Hill |
| Difficulty | grandpa |
| Author | Hiumee |
| KOTH score at close | 142.234, rank 34 of 118 |
| Status | not applicable, scored by ranking |

> What if you had to fight for the flag?
>
> Make your bot compete against the others. The best one wins. 2 minute ticks reward the current rankings. More details in deliverable
>
> Only the latest bot sent to the server will compete. If you submit a bad bot, you can lose positions. You can submit once every 30 seconds. You don't need to re-submit the same bot, it will keep competing

<details>
<summary><b>The Run</b></summary>

King of the Hill pays every two minutes for 24 hours and normalizes the payout against the leading team, so a mediocre bot that is live the whole time beats a good bot submitted at hour twenty. Getting something on the board early was worth four places, because ranks 38 through 41 and 43 all finished on an identical jeopardy score of 2873 and KOTH was the only term separating them.

| rank | team | jeopardy | KOTH |
| ---: | --- | ---: | ---: |
| 38 | Kessoku Band | 2873 | 142.234 |
| 39 | hu/prod/random | 2873 | 137.262 |
| 40 | Selfwash | 2873 | 133.802 |
| 41 | Hexadecimal | 2873 | 120.443 |
| 43 | DCBA | 2873 | 83.297 |

The key finding. The arena served our own match history at `GET /api/replays`, an undocumented endpoint nobody had found. The way in was reading the leaderboard page's own replay player rather than guessing URLs. Before that every decision was justified by self-play, which certified four straight improvements while our rank went from 14 to 16. After it, every decision was a paired measurement on the real field. Every result that survived the contest came out of it, including the one change that measured positive.

## The game

Each team submits a WebAssembly bot plus a loadout of three characters, and matches run continuously in a 3v3 arena capture the flag. A scoring tick every two minutes pays by current arena rank, only the latest bot competes, and a submission can be made once every 30 seconds.

- `update_capture` counts alive bodies inside the radius and moves progress by that count per tick, so three bodies capture three times as fast as one. If both teams have anyone inside, progress freezes completely, which makes one surviving enemy in the circle worth more to them than several kills are to you.
- On reaching `capture_limit` 100 the scoring team gets `full_team_respawn` and `capture_lock` blocks progress for 40 ticks, against a walk home of about 140, so the enemy usually counter-scores. The counter is shared and signed, so a second score needs 196 rather than 100.
- The world is mirrored in the x direction for team 1 and the objective is the arena center either way, so one build plays both sides and every coordinate can be hardcoded.
- The map is static, a fixed 16-box layout copied identically into every match, leaving two lanes to the center plus one clear vertical corridor at x 500 to 680.
- The three classes are asymmetric in a way that decides the loadout.

| | warrior (W) | archer (A) | bandit (B) |
|--|--|--|--|
| max hp | 200 | 100 | 100 |
| fov range | 350 | 900 | 600 |
| ammo, whole match | 20 | 8 | 2 |
| damage | 50 | 50 | 100 |
| attack | melee cone, range 80 | projectile, speed 40 | hitscan, unlimited range |

## The foothold, which is a source read rather than a probe

The handout `capturetheflag-player.zip` ships the engine as C source with a Docker match runner beside it, so the first hour goes on `src/game.c` and `src/wasm_runtime.c` instead of on the live arena.

```
unzip capturetheflag-player.zip && cd capturetheflag-player
cp bot.c sdk/c/example.c
docker build --file sdk/c/Dockerfile --output type=local,dest=./bot-output .
docker run --rm --user "$(id -u):$(id -g)" \
  --mount "type=bind,source=$(pwd),target=/work" ctf-match-runner \
  --config /work/examples/match.json \
  --bot-a /work/a.wasm --bot-b /work/b.wasm --out /work/output
docker run --rm -v "$PWD:/w" -w /w node:22-bookworm \
  node scripts/replay_to_json.js output/player_a.ctfr > /tmp/r.json
```

Five facts come straight out of that source and none of them can be discovered from the observation a bot receives at runtime. Capture is occupancy and freezes when contested; scoring teleports the scorer home; the world is x-mirrored for team 1; the box layout is fixed; and `ctf_shortest_path` is rate limited to three calls per 200 ticks with ten one-tick headings each. The last two together say the interesting thing, since a static map plus a path budget that covers 30 of every 200 ticks means the route should be a table of constants and the path API should never be called at all.

The replay JSON is the debugger. The first three versions each died of something the replay alone could show. Version one walked straight at the center, wedged on the x=680 wall at tick 200 and stood there for 5800 ticks, losing 0-1 to the random example bot; the observation includes zero geometry, so a bot cannot see a wall coming and has to know the map in advance. Version two scored and then walked home into the same wall, because `full_team_respawn` teleports the team without anyone dying and the route index still pointed at the last waypoint, which a teleport test fixes in one line since `move_speed` is 12 and any jump over 40 units in a tick is a respawn. That single fix turned 2-2 into 3-0 in 447 ticks. Version three kept missing with archers, and the `warnings` array in the replay held 32 entries a match reading `action component clamped`, because `ctf_set_move` and `ctf_set_aim` clamp each component to `CTF_DIR_SCALE` independently, so a raw delta of (1900, 100) clips x to 1000 and bends a 3 degree heading to 6.

## How the endpoint was found

The arena's leaderboard is a static bundle served through Cloudflare. The replay player in it is 16 KB of readable JavaScript that names the calls it makes. Reading `replay_view.js` gave `GET /api/replays/<id>/file`, which returns a raw `.ctfr`, and the match list behind it at `GET /api/replays` answered the same cookie session the board login already held. One rule bounds this, contest Rule 01: read only your own list, because enumerating replay ids is a team-wide disqualification.

The list returns one row per opponent, holding their version, our version, the score, the tick count, the termination reason, and a creation timestamp.

```json
{"id": 3476, "opponent": "thehackerscrew", "opponent_version": 10,
 "outcome": "loss", "own_score": 0, "opponent_score": 3,
 "own_version": 4, "ticks": 576, "termination": "capture_limit",
 "created_at": "2026-09-05 11:28:40"}
```

The first pull was 29 matches, 13 wins and 16 losses, and almost every loss was a 0-3 shutout lasting 330 to 743 ticks, several of them against opponent version 2 or 3. A bot on its second submission is not a sophisticated bot, so the shutouts said something structural was wrong with ours.

The tick counts then localized it from our own model alone. Capture limit is 100 and three bodies move progress by 3 a tick, so a capture takes 34 ticks; our route was about 1670 units at 12 units a tick, so a trip is 139 ticks; scoring sends the scorer home, so three scores cost at least 519 ticks without any resistance. maimai did it to us in 330. Either the model was wrong or their route was much shorter than ours, and both alternatives are cheap to test with a downloaded replay.

Replay 4612 answered it. The capture counter is one shared signed integer for both teams, so an opponent's whole schedule is visible even though the file shows enemy bodies only when we could see them. Squid Proxy Lovers v15 scored at ticks 112, 223 and 334, exactly 111 apart, decomposing into 77 ticks of walking and 34 of capturing. Capture speed, the respawn, and the lock were all exactly as modeled, and the only error was route length, 924 units for them against 1670 for us, with our top-corridor detour accounting for 746 units of pure waste.

## What the instrument produced

Four things, in the order they landed.

The route came first. A visibility graph over the configuration-space obstacles, whose corners are rounded because `ctf_circle_static_valid` rejects any sample within 24 units of a box, then Dijkstra and string pulling, with corner clearance swept at 26, 34, 40, and 46 units. Clearance 34 costs 22 units of path and shipped, because there is no wall sliding in this engine and a body that grazes a corner stops dead for the rest of the match. First arrival went from 112 ticks to 85 and first score from 152 to 119.

The move encoding came second and was worth more than the geometry. `desired_displacement` computes `mx * move_speed / isqrt(mx*mx + my*my)` with a truncating root and a truncating divide, per component, so `ctf_set_move(1, 1)` steps (12, 12) while the normalized `(707, 707)` that every bot we had written steps (8, 8). Travel time is therefore Chebyshev distance over 12 and the minor axis is free. Sending small integer vectors took arrival to 73 ticks, first score to 108, and a 3-0 against a passive opponent from 357 ticks to 324. Aim has to stay normalized, since `spawn_arrow` and `in_cone` divide by the vector's own length and only the angle survives.

The adversary pool came third, once it was clear self-play was the problem rather than the bot. Four hand-written instruments, each playing a strategy we never play, run over every loadout pair on both sides.

```
pool/build.sh
pool/harness.py candidate.wasm --name mybot --jobs 8 --json out.json
```

RUSHER sprints and never attacks, so it measures the race. DENIER parks all three bodies in the circle and fights, so it measures whether we can clear it. SNIPER holds range and never enters, so it measures whether we survive the approach. MINIMAL is the control. Over 128 matches the champion won 110, and every single loss was to DENIER, which reproduced the fast 0-3 shutouts of the real board. The replay of one of those losses showed the mechanism: across 460 ticks we had zero or one body inside the circle and never two, because our three bodies walked the same lane 20 to 40 ticks apart and were killed one at a time on arrival.

The loadout came fourth and is the only change all contest that measured positive. A census over 48 loss replays, decoded with the kit's own `replay_to_json.js` and read for enemy `class_id`, found the field clustered hard on three bandits. Bullets needed to clear a team is the sum of `ceil(hp/100)`, which is 6 for WWW, 4 for WBB, and 3 for BBB, and three bandits hold six rounds at 100 damage for 600 total against exactly 600 hit points of WWW. Three warriors therefore arrive dead against most of the board. Switching to BBB moved the named head-to-head row from 1 of 12 to 4 of 12 in a single round and beat two teams we had never beaten in 45 career matches, while the aggregate barely moved. The final answer was WBB, measured at +1 of 97 ahead of BBB, because a 200 hp warrior takes two bullets to clear a corridor that one-shots a 100 hp bandit.

## Holding it for 24 hours

Always pass the loadout explicitly. The default in our submit wrapper was warrior, archer, bandit. A bare submit ships a silent loadout change stacked on a code change. The result becomes uninterpretable. The JSON shape is an array of objects with `name` and `class`. The obvious guess of a bare array of class strings returns HTTP 400 `character 1 is invalid`.

```
koth submit camper8.wasm \
  --loadout '[{"name":"atlas","class":"warrior"},
              {"name":"vega","class":"bandit"},
              {"name":"kite","class":"bandit"}]'
```

A watcher polled the board every minute into a series log, recording version, record, rank, arena submission counter, and a row of named head-to-head results. Two operational lessons came out of running it for a day. Start it under `setsid`, because it twice died with its parent shell and each death cost about twelve minutes of unrecorded board history. Make it fail loudly, because the API helper returns a list on success and a dict on any error, and the naive filter over rows iterates the dict's keys and raises `AttributeError` the moment a cookie lapses.

The rollback trigger watched the named head-to-head row and never the rank. Rank measures the field, and it slid from 39 to 44 in one window while the head-to-head row stayed byte-identical and the field grew from 81 teams to 103. Rounds matter rather than polls, since a round of matches takes about 15 minutes while the watcher samples every minute, so a trigger counting polls fires roughly fifteen times too eagerly.

The most useful operational finding arrived late. The same binary with the same loadout, submitted eight minutes apart as versions 32 and 34 with the field actively resubmitting in between, produced 103 of 104 identical outcomes and a paired net of zero over 87 same-version pairs. The engine is deterministic and the noise floor we had been assuming never existed; the drift was opponents shipping past us, with 42 of our 104 head-to-heads replayed under us inside one 75-minute window. A paired same-version comparison of two replay pulls is therefore an exact measurement, while the board aggregate is worthless for judging a change.

The arena went down twice, and the series log shows the outage as HTTP 521 from Cloudflare rather than as a collapse in our record. Submitting into a dark board is unreadable by construction, so the rule during an outage is to build locally and hold.

## The dead ends, which were most of the contest

Every code change between 16:49 and 22:57 on day one is collectively worth between -1 and +1 matches out of about 90, measured pairwise. The list is worth more than the survivors.

- camper3, a sweep for the aim of a seated body when the capture counter is provably frozen. The detector armed on 0 of 6001 ticks, because in the mode we lose nobody is inside the circle to freeze anything.
- camper5, a perpendicular unstick for a genuine movement deadlock. It converted a lab match from 0-0 at the 6000 tick limit to 3-0 in 1222 ticks, then produced an arena replay whose md5 matched the previous version's byte for byte, which proves the branch never fired against a real opponent.
- camper6, turning a seated body to face the only direction a threat can arrive from. The branch provably fires and changed no outcome anywhere.
- The acquisition floor, shipped twice as versions 22 and 24 and reverted both times on measurement.
- The archer, five arena cycles that came back a clean negative. AAA measured -32 of 94, WBA -20 of 93, WWA -22 of 91, and WAB -16 of 87, so the penalty is about 22 matches per archer slot and has nothing to do with hit points.

Opponent-adaptive play deserves its own paragraph, because it looked like the best idea of the night. Opponent composition is readable after the fact from `class_id` on enemy sightings in the replay files, and of 73 same-opponent-version pairs, 28 provided a complete three-body read.

| opponent bandits | WWW-only | WBB-only | both | neither |
|---|---|---|---|---|
| 0 | 0 | 0 | 4 | 1 |
| 1 | 0 | 1 | 5 | 0 |
| 2 | 0 | 1 | 1 | 1 |
| 3 (BBB) | 6 | 0 | 4 | 6 |

Every opponent with a complete read that only WWW beats is BBB, six of six, and no BBB opponent is ever beaten by WBB alone, so the damage arithmetic above shows up in the record as a knife edge. Three blockers kill the idea anyway. The loadout is a submission parameter and the WebAssembly module cannot change it mid-match, opponent classes are unreadable at tick 0, and the WWW column confounds the binary with the loadout it shipped under.

Nine candidates were refused on the argument that no single deployment could separate a real gain from noise, and the engine was deterministic all along. The only positive result came from testing a candidate the lab had refuted.

## What it scored: what is missing from this directory

We finished on 142.234 KOTH points at 0.1163 a tick, against a leader on 1542.61 at 3.7500, so 24 hours of holding mid-table converted to 1.844 of the 20 points KOTH contributes to the overall score. KOTH rank was 34 of 118 and arena rank at close was 54.

No live arena screenshot exists, since I forgot to capture one while the contest was running. By 13:17Z the next day `game.koth.pro` answered HTTP 521 from Cloudflare on every origin-served route, which leaves that gap permanent. The 62W 0D 45L at arena rank 50 that appears in the series log is a 03:45Z reading rather than a final standing. Everything captured after the close is in `artifacts/`, indexed by `artifacts/CAPTURE-INDEX.md`. The working ledger behind every number above is in `analysis/`, where four files hold most of it.

- `FINDINGS.md`, the five engine facts and the three bugs that produced them.
- `ROUTE.md` and `ROUTE-SPEED.md`, the route geometry together with the move encoding.
- `POOL.md`, the four adversaries plus the harness that runs them.
- `ENDGAME.md`, the 24-hour log, holding every arena cycle and the prediction registered before it.

</details>
