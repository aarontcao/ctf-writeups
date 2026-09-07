# KOTH challenge: Capture the Flag?

Captured 2026-09-06T13:23:19Z from the TFC CTF platform API `GET /koth` (HTTP 200).

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

- `reporting_mode` is `rankings`: the arena reports each team a rank, the platform converts rank to points.
- Ticks are 2 minutes. Each tick pays `points_per_tick` based on the current arena rank, and the payout accumulates for the whole 24 hours.
- `points_per_tick` observed range at close: 0.0529 (worst) to 3.7500 (rank 1).
- The KOTH total then enters the overall score normalised against the field leader: `koth/max_koth*20`, so KOTH is 20 of the 100 available points.
- Only the latest bot submitted competes. A bad submission loses positions. Submission rate limit is one per 30 seconds.

## The payout curve was brutal

Leader `maimai` finished on 1542.61 points at 3.7500 per tick. We finished on 142.23 at 0.1163 per tick, a factor of 32.2. Because the overall contribution is normalised against the leader, our 24 hours of holding a mid-table arena rank converted to 1.84 of the 20 available points.
