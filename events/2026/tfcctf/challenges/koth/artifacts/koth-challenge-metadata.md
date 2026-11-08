# KOTH challenge: Capture the Flag?

Captured 2026-09-06T13:23:19Z from the platform's `GET /koth`.

| field | value |
| --- | --- |
| challenge_id | `6b173e0d-2e32-4ab4-8812-ba3c7bceb2db` |
| author | Hiumee |
| category | misc (`c76d2ce0-8d43-4304-8da0-65d861b7afcf`) |
| connection_mode | external |
| reporting_mode | `rankings` |
| connection_string | https://game.koth.pro/ |
| is_dynamic | False |
| handout | capturetheflag-player.zip |
| handout_url | https://api.ctf.thefewchosen.com/challenge-files/capturetheflag-player_1139fe432118d722.zip |

## Description
```
What if you had to fight for the flag?

---

Make your bot compete against the others. The best one wins. 2 minute ticks reward the current rankings. More details in deliverable



Only the latest bot sent to the server will compete. If you submit a bad bot, you can lose positions. You can submit once every 30 seconds. You don't need to re-submit the same bot, it will keep competing
```

## Scoring rules

- The arena reports each team's rank and the platform converts it to points (`reporting_mode` `rankings`).
- Every 2-minute tick for 24 hours pays `points_per_tick` by current arena rank.
- At close, `points_per_tick` ran from 0.0529 to 3.7500 (rank 1).
- KOTH enters the overall score as `koth/max_koth*20`.

## Payout curve

Leader `maimai` finished on 1542.61 points at 3.7500 per tick. We finished on 142.23 at 0.1163, a per-tick factor of 32.2. Our 24 hours in the arena earned 1.84 of the 20 KOTH points.
