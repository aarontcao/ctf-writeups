# Thematic

| | |
|---|---|
| Event | UIUCTF 2017 |
| Category | recon |
| Points | 100 |
| Status | solved |

> Infosec twitter is a remarkable place.
>
> https://www.youtube.com/watch?v=e-ORhEE9VVg

Backfill note, and the evidence here is one tweet. What survives on disk is the flag, the tweet id, and its timestamp, which leaves the search itself uncaptured and leaves nothing here to run. The ladder below is reconstructed from the challenge text and from the shape of the event, so read it as the path the challenge was built to make obvious rather than as a log of ours.

<details>
<summary><b>Solution</b></summary>

The key observation is that the flag was never posted by the organizers, so their timeline lacks it. The search runs over their mentions instead.

The video in the description is Blank Space, which names the theme the whole event ran on. UIUCTF 2017 was Taylor Swift themed end to end, down to a reverse engineering challenge called Taylor's Magical Flag Oracle whose flag is `flag{trchrus}`, so a reader who follows the link learns which corner of infosec Twitter the first line is pointing at. The sibling recon challenge, [Baby's First Recon](../babys-first-recon/), had already established the organizers' Twitter presence as the surface, and the two challenges are plainly meant to be read together.

Searching what the organizers posted turns up nothing, and the query that works is `to:UIUCTF flag`, over what was posted at them. The reply came from [@SwiftOnSecurity](https://x.com/SwiftOnSecurity/status/858092845886046209), the parody account that is the natural intersection of Taylor Swift and infosec Twitter, which is the joke the challenge title is making.

> @UIUCTF flag{-uiuc.tf_l0v3s_taylor-} https://uiuc.tf/

Tweet id `858092845886046209`, posted 2017-04-28 22:57:31 UTC, about an hour before the CTF opened. The timing is the one detail that makes this findable in a hurry, since anything posted at the organizers within an hour of the opening whistle is a short list however you sort it.

Flag: `flag{-uiuc.tf_l0v3s_taylor-}`
</details>
