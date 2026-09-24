# KOTH evidence capture index

Some of the figures below might differ from the final leaderboards/scoreboards slightly because I took captures before the last couple of hours of the contest (and then went to bed).

| term | value |
| --- | --- |
| jeopardy score | 2873 |
| KOTH score | 142.234 |
| normalised jeopardy, out of 80 | 53.576 |
| normalised KOTH, out of 20 | 1.844 |
| total | 55.420 |
| last jeopardy solve | 2026-09-05T17:13:14Z |

Scoring formula: `total = jeopardy/max_jeopardy*80 + koth/max_koth*20`, with `max_jeopardy` 4290 and `max_koth` 1542.606.

## My final KOTH record

The bot record of **62W 0D 45L at arena rank 50, arena submission 5654** I got from `board-series.log` at 03:45Z (not necessarily the final standing). The confirmed final figures from the platform are arena `current_rank` **54** and points `score_rank` **34 of 118**.

## Files

| file | what it shows | captured |
| --- | --- | --- |
| `arena-down-probe-1320Z.txt` | Full response headers for six arena paths, showing 521 on every origin-served route and 200 only on the cached static asset. | 13:17Z |
| `arena-static-app.js` | Cloudflare-cached arena leaderboard renderer, 4986 bytes. Source of the `data-href="/replay/<id>"` row contract. | 13:17Z |
| `arena-static-replay_view.js` | Cloudflare-cached replay player, 16148 bytes. Contains the `GET /api/replays/<id>/file` call our downloader was built on. | 13:18Z |
| `scoreboard-final-all-raw.json` | Complete scoreboard, `scope=all`, 1017 teams, every scoring term per team. | 13:21Z |
| `scoreboard-final-open-raw.json` | Open division, 612 teams. | 13:21Z |
| `scoreboard-final-classic-raw.json` | Classic division, 405 teams. | 13:21Z |
| `scoreboard-final-all.txt` | Human-readable top 10 and ranks 33 to 44, our row marked. | 13:21Z |
| `scoreboard-final-all.png` | Termshot of the above, our row boxed. | 13:21Z |
| `koth-final-standings-raw.json` | Complete `GET /koth` response, 118 teams, frozen at `best_submitted_at` 2026-09-06T09:59:30Z, plus the challenge object. | 13:19Z |
| `koth-final-standings.txt` | Readable KOTH table, top 12 and ranks 29 to 40, our row marked. | 13:23Z |
| `koth-final-standings.png` | Termshot of the above. | 13:23Z |
| `koth-challenge-metadata.md` | The KOTH challenge description verbatim, its ids, handout URL, and the scoring rules as the platform implemented them. | 13:23Z |
| `ctf-board.txt` / `.png` | The challenge board. Post-close values. | 13:22Z |
| `ctf-team.txt` / `.png` | The team object. Invite token redacted by the CLI before capture | 13:22Z |
