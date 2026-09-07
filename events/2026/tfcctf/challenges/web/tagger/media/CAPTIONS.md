# Tagger

![register page](01-register-page.png)

The username regex is `/^[a-zA-Z0-9_ ]{3,32}$/`, so you can put a space in a username.

![the chat app](02-chat-app.png)

Express 5, EJS, sqlite, and a puppeteer bot on a 60 second cycle.

![the cache key confusion](03-cache-key-bug.png)

`getMessageHistory` keys on `${userA.trim()}:${userB.trim()}`. Register `Hacker ` and `FlagHolder ` with trailing spaces and you collide with the real pair. TTL is 60 s and the bot cycle is 60 s.

![the markup sink and the CSP](04-markup-sink-and-csp.png)

`messageRecord` copies every Message attribute from the body except four, so `type`, `tagName` and `attributes` are ours. The image path emits `<img{attrs}>` with attribute names `/^[a-z]+$/` and values `/^[a-zA-Z0-9,. =]*$/`. `script-src-attr 'unsafe-inline'` means inline handlers run.

![the bot cycle](05-bot-cycle.png)

`visitAsHacker` opens the conversation and waits 3 s. `replyAsFlagHolder` posts `process.env.FLAG` only if the Hacker conversation preview is exactly `Give me the flag!`. You have to put that message there yourself.

![the cache collision, live](06-cache-collision.png)

Our chat and the bot's chat now read the same key.

![the exploit request](07-exploit-request-net.png)

You get no parens and no quotes in an attribute value, but `zp.innerHTML=zq.textContent` is legal under the charset and gives arbitrary HTML with unrestricted inline handlers.

![the flag lands in the shared cache](08-flag-in-cache.png)

The XSS posts the magic string as Hacker, then FlagHolder replies with the flag on the next cycle.

![the run](09-exploit-run.png)

It landed two for two on a clean container. I kept a collector channel as a backup and ended up not needing it.

![the flag](10-flag.png)
