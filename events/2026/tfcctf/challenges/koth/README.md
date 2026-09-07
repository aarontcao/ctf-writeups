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

Focusing on KOTH early actually got me 4 ranks/placements on the leaderboard! Ranks 38 through 41 and 43 all finished on an identical jeopardy score of 2873, so KOTH was the only thing that separated us haha

| rank | team | jeopardy | KOTH |
| ---: | --- | ---: | ---: |
| 38 | Kessoku Band | 2873 | 142.234 |
| 39 | hu/prod/random | 2873 | 137.262 |
| 40 | Selfwash | 2873 | 133.802 |
| 41 | Hexadecimal | 2873 | 120.443 |
| 43 | DCBA | 2873 | 83.297 |

## The game

The game was 3v3 arena capture the flag. Each team submits a WebAssembly bot plus a loadout of three classes. Matches run continuously and a tick every two minutes rewards the current rankings normalised against the leader, and only your latest bot competes.
- `update_capture` counts alive bodies inside the radius and moves progress by that count per tick, so 3 bodies capture 3 times as fast as one. But if *both* teams have anyone inside, progress freezes completely. One surviving enemy in the circle is worth more to them than several kills are to you.
- On reaching `capture_limit` 100 the scoring team gets `full_team_respawn`, and `capture_lock` blocks progress for 40 ticks while the walk back is about 140, so the enemy usually counter-scores. The counter is shared and signed, so your *next* capture needs 196 rather than 100. For instance, my second score took 252 ticks, and both of the opponent's goals came during that.
- The world is mirrored in the x-direction for team 1, and the point is the arena centre either way, so one build plays both sides and every coordinate can be hardcoded.
- The map is static (a fixed 16-box layout memcpy'd identically every match), with two lanes to the centre plus one clear vertical corridor.
- Asymmetric classes:

| | warrior (W) | archer (A) | bandit (B) |
|--|--|--|--|
| max hp | **200** | 100 | 100 |
| fov range | 350 | **900** | 600 |
| ammo, whole match | **20** | 8 | **2** |
| damage | 50 | 50 | **100** |
| attack | melee cone, range 80 | projectile, speed 40 | **hitscan, unlimited range** |

## Stuff I tried

Mostly I tinkered and tuned army composition/loadout. Later on I tried to come up with heuristics based on opponent bandit count. You can infer opponent army composition from `class_id` on enemy sightings in the replay files. One neat thing I noticed was that, of the 73 same-opponent-version pairs, 28 had a complete three-body read:

| opponent bandits | WWW-only | WBB-only | both | neither |
|---|---|---|---|---|
| 0 | 0 | 0 | 4 | 1 |
| 1 | 0 | 1 | 5 | 0 |
| 2 | 0 | 1 | 1 | 1 |
| **3 (BBB)** | **6** | **0** | 4 | 6 |

Every WWW-only opponent with data is BBB, six of six, and no BBB opponent is ever WBB-only. A BBB team carries six rounds at 100 damage, so 600 in total, and three warriors come to the same 600 hit points. A bandit one-shots any 100 hp body. So against BBB survivability is the whole game and WWW sits right on the edge. Against a warrior-bearing team, hit points don't save you. I couldn't find any way to exploit this though, since opponent classes aren't readable at tick 0, so even a hypothetical mid-match switch wouldn't have anything to switch on.

## Screenshots, captures, and final standing

Unfortunately I forgot to take screenshots or captures during when the game was actually live wop wop. So my recorded bot record of 62W 0D 45L at arena rank 50 is from the final logs I had access to at 03:45Z (my final standing was a bit worse). The final leaderboard showed arena `current_rank` 54 and points `score_rank` 34 of 118.
</details>
