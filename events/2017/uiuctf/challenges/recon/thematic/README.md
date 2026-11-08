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

Only the flag and the tweet survived, so I reconstructed the search.

<details>
<summary><b>Solution</b></summary>

The flag isn't on the organizers' timeline. It's in a reply to them, from the account where Taylor Swift meets infosec Twitter.

The linked video is Taylor Swift, like the rest of the event. The query `to:UIUCTF flag` searches posts aimed at the organizers and finds the reply from [@SwiftOnSecurity](https://x.com/SwiftOnSecurity/status/858092845886046209).

> @UIUCTF flag{-uiuc.tf_l0v3s_taylor-} https://uiuc.tf/

Flag: `flag{-uiuc.tf_l0v3s_taylor-}`
</details>
