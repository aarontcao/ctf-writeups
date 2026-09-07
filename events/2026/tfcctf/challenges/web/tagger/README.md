# Tagger

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | web |
| Difficulty | grandpa |
| Author | Sagi |
| Points at close | 132 |
| Solves | 113 |
| Status | solved |

> Look at my new chat app, Tagger!!!

Files: [`challenge.zip`](handout/challenge.zip)

<details>
<summary><b>My Solution</b></summary>

Usernames allow spaces and the message-history cache key is `${userA.trim()}:${userB.trim()}`, so register `Hacker ` and `FlagHolder ` with trailing spaces and you collide with the bot's own conversation. The app is Express 5, EJS, sqlite, and a puppeteer bot, with this CSP:
```
default-src 'self'; script-src 'self' 'unsafe-eval';
script-src-elem 'self'; script-src-attr 'unsafe-inline';
object-src 'none'; base-uri 'none'
```
So inline event handlers run, an injected `<script src>` doesn't, and you have to exfiltrate with a navigation rather than a fetch. The bot runs every 60 seconds. `visitAsHacker` opens the conversation with FlagHolder and waits 3 s, then `replyAsFlagHolder` posts `process.env.FLAG`, but only if the Hacker conversation preview reads exactly `Give me the flag!`. Nothing seeds that message for you, so the flag ends up as an ordinary DB row and you have to make the preview say it first. That's what the cache key gets you.

Finish with some important details
- the username regex is `/^[a-zA-Z0-9_ ]{3,32}$/`, so spaces are allowed, and `.trim()` in the key collapses `Hacker ` onto `Hacker`
- TTL is 60 s against a 60 s bot cycle, which is tight but fine
- `messageRecord` copies every Message attribute from `req.body` except `id`, `fromUserId`, `toUserId`, and `sentAt`, so `type`, `tagName`, `attributes`, and `content` are all yours through mass assignment
- the `type=image` path emits `<img{attrs} class="message-image" src="...">` with `attrs` from your JSON, attribute names matching `/^[a-z]+$/` and values `/^[a-zA-Z0-9,. =]*$/`
- no parens and no quotes in an attribute value sounds fatal but isn't, because `zp.innerHTML=zq.textContent` is legal under that charset
- `content` is unescaped at the DOM text level, so it can carry the payload

That gets you arbitrary HTML with unrestricted inline handlers. From there the XSS runs as Hacker in the bot's browser and posts the magic string, and the next cycle has FlagHolder reply with the flag into the cache you share. Landed it twice on a clean container.

Flag: `TFCCTF{Tagg3r_m15C0muN1cA710n}`
</details>
