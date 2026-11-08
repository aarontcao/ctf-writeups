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

King of the Hill pays every two minutes for 24 hours, normalized against the leading team. So a mediocre bot that's live the whole time beats a good one submitted at hour twenty. Ranks 38 through 41 and 43 all finished on a jeopardy score of 2873, so KOTH alone ordered them. The KOTH work was worth four places to us.

| rank | team | jeopardy | KOTH |
| ---: | --- | ---: | ---: |
| 38 | Kessoku Band | 2873 | 142.234 |
| 39 | hu/prod/random | 2873 | 137.262 |
| 40 | Selfwash | 2873 | 133.802 |
| 41 | Hexadecimal | 2873 | 120.443 |
| 43 | DCBA | 2873 | 83.297 |

The key observation is that the arena served our own match history at `GET /api/replays`. Before that, self-play certified four straight improvements while our rank went from 14 to 16. After it, every decision was a paired comparison on the real field.

## The game

Each team submits a WebAssembly bot and a loadout of three characters for continuous 3v3 capture the flag.

- `update_capture` moves progress by the number of alive bodies inside the radius, so three bodies capture three times as fast as one. If both teams have anyone inside, progress freezes. One surviving enemy in the circle is then worth more to them than several kills are to you.
- On reaching `capture_limit` 100 the scoring team gets `full_team_respawn`, and `capture_lock` blocks progress for 40 ticks. The walk back takes about 140, so the enemy usually counter-scores. The counter is shared and signed, so our second score needed 196.
- Team 1's world is mirrored in x around the central objective, so one build plays both sides with hardcoded coordinates.
- The map is a fixed 16-box layout, leaving two lanes to the center plus a clear vertical corridor at x 500 to 680.

The class numbers decide the loadout.

| | warrior (W) | archer (A) | bandit (B) |
|--|--|--|--|
| max hp | 200 | 100 | 100 |
| fov range | 350 | 900 | 600 |
| ammo, whole match | 20 | 8 | 2 |
| damage | 50 | 50 | 100 |
| attack | melee cone, range 80 | projectile, speed 40 | hitscan, unlimited range |

## Reading the engine

The handout `capturetheflag-player.zip` ships the engine as C source with a Docker match runner, so the first hour went on `src/game.c` and `src/wasm_runtime.c`.

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

The box layout is fixed, and `ctf_shortest_path` is rate limited to three calls per 200 ticks with ten one-tick headings each. That covers 30 of every 200 ticks, so the route should be a table of constants and the path API never gets called.

The replay JSON is the debugger. Our first bot walked straight at the center and wedged on the x=680 wall at tick 200. The observation doesn't include any geometry, so a bot has to know the map in advance.

The second bot scored, then walked home into the same wall. `full_team_respawn` teleports the team without anyone dying, so the route index still pointed at the last waypoint. `move_speed` is 12, so any jump over 40 units in a tick is a respawn. Testing for that turned 2-2 into 3-0.

Archer-heavy builds kept missing, and the replay's `warnings` array held 32 entries a match reading `action component clamped`. `ctf_set_move` and `ctf_set_aim` clamp each component to `CTF_DIR_SCALE` independently. A raw delta of (1900, 100) clips x to 1000 and bends a 3 degree heading to 6.

## Finding the replays

The leaderboard's replay player, `replay_view.js`, is readable JavaScript that names its calls. It gave `GET /api/replays/<id>/file`, which returns a raw `.ctfr`. The match list at `GET /api/replays` answered the cookie session the board login already held. Contest Rule 01 says to read only your own list, since enumerating replay ids is a team-wide disqualification.

```json
{"id": 3476, "opponent": "thehackerscrew", "opponent_version": 10,
 "outcome": "loss", "own_score": 0, "opponent_score": 3,
 "own_version": 4, "ticks": 576, "termination": "capture_limit",
 "created_at": "2026-09-05 11:28:40"}
```

The first pull was 29 matches, 13 wins and 16 losses. Almost every loss was a 0-3 shutout in 330 to 743 ticks, several against opponent version 2 or 3.

The tick counts located the fault. Three bodies capture in 34 ticks, and our 1670 unit route took 139 ticks at 12 a tick. Scoring sends the scorer home, so three scores cost at least 519 ticks without any resistance. maimai did it to us in 330.

Replay 4612 explained it. Both teams share one signed capture counter, so it shows the opponent's whole schedule even when their bodies are out of sight. Squid Proxy Lovers v15 scored at ticks 112, 223, and 334, exactly 111 apart: 77 ticks of walking and 34 of capturing. Our capture model was right. Their route was 924 units and ours was 1670, with 746 of ours wasted on a detour through the top corridor.

## What the replays fixed

We rebuilt the route as a visibility graph with rounded corners, since `ctf_circle_static_valid` rejects any sample within 24 units of a box. Dijkstra finds the shortest path and string pulling straightens it. The engine doesn't slide bodies along walls, so a body that grazes a corner stops dead for the rest of the match. A corner clearance of 34 costs 22 units of path and shipped. First arrival went from 112 ticks to 85 and first score from 152 to 119.

The move encoding was worth more than the geometry. `desired_displacement` computes `mx * move_speed / isqrt(mx*mx + my*my)` per component, with a truncating root and a truncating divide. So `ctf_set_move(1, 1)` steps (12, 12), while the normalized `(707, 707)` we'd been sending steps (8, 8). Travel time is Chebyshev distance over 12, and the minor axis is free. Small integer vectors took arrival to 73 ticks, first score to 108, and a 3-0 against a passive opponent from 357 ticks to 324. Aim has to stay normalized, since `spawn_arrow` and `in_cone` divide by the vector's own length and only the angle survives.

Self-play was the real problem, so we wrote four adversaries that each play a strategy we never play. The harness runs them over every loadout pair on both sides.

```
pool/build.sh
pool/harness.py candidate.wasm --name mybot --jobs 8 --json out.json
```

Over 128 matches the champion won 110, and every loss was to DENIER, which parks all three bodies in the circle and fights. In one of those losses we never had two bodies inside the circle across 460 ticks. Our three walked the same lane 20 to 40 ticks apart and died one at a time.

The loadout was the only change all contest that came out positive. Enemy `class_id` in the replays showed the field clustered hard on three bandits. The bullets needed to clear a team are the sum of `ceil(hp/100)`, so 6 for WWW, 4 for WBB, and 3 for BBB. Three bandits hold six rounds at 100 damage, exactly the 600 hit points of WWW, so three warriors arrive dead against most of the board.

Switching to BBB moved the named head-to-head row from 1 of 12 to 4 of 12 in a single round, while the aggregate barely moved. It beat two teams we had never beaten in 45 career matches. WBB finished +1 of 97 ahead of BBB, since a 200 hp warrior takes two bullets where a 100 hp bandit takes one.

Archers lost every time. Paired against WBB, AAA came in at -32 of 94, WBA -20 of 93, WWA -22 of 91, and WAB -16 of 87. That's about 22 matches per archer slot, whatever the hit points.

## Holding it for 24 hours

Always pass the loadout explicitly. Our submit wrapper defaulted to warrior, archer, bandit, so a bare submit stacks a silent loadout change on a code change. The JSON is an array of objects with `name` and `class`. A bare array of class strings returns HTTP 400 `character 1 is invalid`.

```
koth submit camper8.wasm \
  --loadout '[{"name":"atlas","class":"warrior"},
              {"name":"vega","class":"bandit"},
              {"name":"kite","class":"bandit"}]'
```

Roll back on the named head-to-head row, never on rank. Rank slid from 39 to 44 in one window while the row stayed byte-identical and the field grew from 81 teams to 103. A round of matches takes about 15 minutes, so count rounds, not one-minute polls.

The engine is deterministic. The same binary and loadout, submitted eight minutes apart as versions 32 and 34, gave 103 of 104 identical outcomes. The paired net over 87 same-version pairs was zero. The drift we had blamed on noise came from opponents resubmitting, and 42 of our 104 head-to-heads were replayed inside one 75-minute window. A paired same-version comparison of two replay pulls is exact, and the board aggregate can't judge a change.

## Adapting to the opponent

Picking the loadout per opponent looked promising. Enemy composition shows up after the fact in `class_id` on enemy sightings, and 28 of 73 same-opponent-version pairs gave a complete three-body read.

| opponent bandits | WWW-only | WBB-only | both | neither |
|---|---|---|---|---|
| 0 | 0 | 0 | 4 | 1 |
| 1 | 0 | 1 | 5 | 0 |
| 2 | 0 | 1 | 1 | 1 |
| 3 (BBB) | 6 | 0 | 4 | 6 |

Every opponent that only WWW beats is BBB, six of six. A bot can't use that, since the loadout is fixed at submission and enemy classes aren't visible at tick 0.

## What it scored

We finished on 142.234 KOTH points at 0.1163 a tick, against a leader on 1542.61 at 3.7500. That came to 1.844 of the 20 points KOTH adds to the overall score. Arena rank at close was 54.

I didn't capture a live arena screenshot during the contest. By 13:17Z, three hours after the close, `game.koth.pro` answered HTTP 521 from Cloudflare on every origin-served route. The series log's 62W 0D 45L at arena rank 50 dates from 03:45Z, hours before the close. Everything captured after the close is in `artifacts/`, indexed by `artifacts/CAPTURE-INDEX.md`.

</details>
