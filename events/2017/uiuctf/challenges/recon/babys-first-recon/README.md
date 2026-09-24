# Baby's First Recon

| | |
|---|---|
| Event | UIUCTF 2017 |
| Category | recon |
| Points | 50 |
| Author | Eric Hennenfent |
| Solves | 28 |
| Status | solved |

> Go stalk the organizers on twitter for a bit and see what you find.

Backfill note. Michael's [writeup](https://mzhang.io/posts/2017-05-01_uiuctf-2017-writeups/) skipped this one, so the recorded account of it is [Valar_Dragon's writeup](https://hgarrereyn.gitbooks.io/th3g3ntl3man-ctf-writeups/content/2017/UIUCTF/problems/Recon/Babys_First_Recon/) for Th3g3ntl3man, which matches what we did. Nothing on disk records our own search, so the two tweets below are quoted from that writeup and the step order is reconstructed from the challenge text and the scoreboard metadata. There is no capture to show, and a reader retracing this today needs an X account, since the search itself now sits behind a login.

<details>
<summary><b>Solution</b></summary>

The key observation is that the flag predates the CTF by eighteen months, so scrolling anyone's timeline around the event yields no results. The move is a keyword search across an account's whole history.

The challenge names no account. The scoreboard's author field reads Eric Hennenfent, so the target is [@Eric_Hennenfent](https://x.com/Eric_Hennenfent).

From there the search is one query, `from:Eric_Hennenfent flag`, which returns the flag posted on 17 October 2015.

> flag{71dedc47f69e66164f7a32da27b7a660}

The same query returns the decoy, posted 8 May 2016, and the account labels it as such on your behalf.

> fd418ab7409c90cb3c2d66a2eabae30d5c671062004c1dd2882b56e77ba653cc - This is not a CTF flag, for anyone that finds this later.

Twenty-eight teams solved this.

Flag: `flag{71dedc47f69e66164f7a32da27b7a660}`
</details>
