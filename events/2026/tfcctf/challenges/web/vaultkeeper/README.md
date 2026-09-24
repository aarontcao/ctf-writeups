# Vaultkeeper

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | web |
| Difficulty | baby |
| Author | skyv3il |
| Points at close | 168 |
| Solves | 91 |
| Status | solved |

> Self-hosted backup & restore appliance,schedule snapshots, ship them anywhere,roll a site back

Files: [`src-current`](handout/src-current), [`vaultkeeper-source-STALE-1014.zip`](handout/vaultkeeper-source-STALE-1014.zip), [`vaultkeeper-source.zip`](handout/vaultkeeper-source.zip)

<details>
<summary><b>Solution</b></summary>

## The insight

The challenge sat for five hours on a single missing input, the sixteen-character
file `/var/www/private/cap.mask`. The template renderer refuses to print it.
One request ended the challenge:

```
POST /api/render_template.php
{"event":"maintenance.x","template":"[[config.cap_mask|at:0|code|sub:200|bar:.]]"}
```

`bar` is `str_repeat((string) $arg, (int) $subject)`, it is the only filter in the engine
that turns its subject into an integer count rather than a string, and PHP 8 raises
`ValueError` when `str_repeat` is handed a negative count. The renderer catches a throw
once per span and returns that span verbatim, so the rendered body reads `[redacted]`
when `ord(mask[0]) >= 200` and reads the literal text `[[config.cap_mask|at:0|code|sub:200|bar:.]]`
when it does not. That is a comparison operator aimed at a value the engine will never
show you. Binary search on the threshold settles one character in about seven probes.
The full mask of 112 requests recovers all sixteen characters. Both responses are recorded verbatim in
`artifacts/remote-evidence.txt`.

Stage A below had to succeed first. Without it no request from outside reaches a loopback-only script. The second prerequisite
cost the five hours, because the `bar` filter is absent from the handout we worked from,
the organizers having replaced the zip in place at 12:41 UTC with nobody re-downloading it.

## Recon, in the order it ran

```bash
unzip -q vaultkeeper-source.zip -d scratch/vaultkeeper
find scratch/vaultkeeper -type f | wc -l          # 96
cat scratch/vaultkeeper/Dockerfile
cat scratch/vaultkeeper/apache/vaultkeeper.conf
grep -rn 'unserialize(' scratch/vaultkeeper/src/
grep -rnE 'query\(.*\$|exec\(.*\$' scratch/vaultkeeper/src/lib/
```

The Dockerfile explains why a PHP challenge ships an Apache config at all. It pins
`php:8.2.12-apache-bullseye` by digest, runs
`apt-mark hold apache2 apache2-bin apache2-data`, copies `php-fpm` in from a second
image, and `entrypoint.sh` opens with a version check that aborts the container unless
`apache2 -v` reports exactly 2.4.56. An author who pins a web server that hard is pinning
it for a reason.

`apache/vaultkeeper.conf` says what the reason is. Two `FilesMatch` blocks fence off five
scripts by basename. A third rule routes every `.php` to php-fpm over mod_proxy:

```apache
<FilesMatch "\.php$">
    SetHandler "proxy:fcgi://127.0.0.1:9000"
</FilesMatch>
<FilesMatch "^(fetch_source|peer_probe|webhook_test)\.php$">
    Require ip 127.0.0.1
</FilesMatch>
<FilesMatch "^(keyring|vault_unseal)\.php$">
    Require ip 127.0.0.1
</FilesMatch>
```

A pinned 2.4.56, an ACL keyed on a basename, and `SetHandler proxy:fcgi` together are the
exact preconditions for the filename confusion bypass published as
[CVE-2024-38473](https://nvd.nist.gov/vuln/detail/CVE-2024-38473), one of the Apache
confusion attacks Orange Tsai presented at Black Hat USA 2024. Apache matches `FilesMatch`
against the basename of the decoded path, so `fetch_source.php%3Fa.php` decodes to a
basename of `fetch_source.php?a.php`, which the pattern misses and the `Require ip`
therefore never applies to. mod_proxy then builds the FastCGI request and truncates the
path at the `?`, so php-fpm receives `SCRIPT_FILENAME=/var/www/html/public/api/fetch_source.php`
and runs it anyway.

The two greps decide what the ACL is protecting. `unserialize(` lands in
`src/lib/restore_state.php`, where `RestorePoint::__unserialize` is followed by a
`__destruct` that writes `$this->ctx->sink[$this->ctx->slot] = $this->snapshot` through
`ArrayAccess`, and in `src/lib/recovery.php`, which is a second sink with its own gadget
set. The SQL grep lands on one interpolated identifier, inside `vk_import_database`:

```php
$pdo->exec("DROP TABLE IF EXISTS `vk_restore`.`$name`");
```

So by the end of the read the shape of the challenge is fixed, with an ACL bypass to get
in, a deserialization gadget chain at the far end, an injectable table name in the middle,
and a key called `cap_key` gating both of the last two. Everything after this is finding out how
`cap_key` is reachable.

## Building a target that answers questions for free

The platform gives out one-hour instances with a team-wide cap of three, so the first
thing to do with a handout this large is stop needing the remote:

```bash
docker build -t vaultkeeper-local scratch/vaultkeeper
docker run -d --name vk -p 18080:80 -e FLAG='TFC{local_test_do_not_submit}' vaultkeeper-local
docker exec vk cat /var/www/private/cap.mask     # the planted answer, for controls
```

Every measurement in the rest of this writeup that could be taken locally was taken
locally, including the PHP 8.2 semantics the oracle depends on, which `docker exec vk php -r`
settles in a second each.

## Stage A: reach a loopback-only script from outside

```bash
curl -s -o /dev/null -w '%{http_code}\n' http://127.0.0.1:18080/api/fetch_source.php
# 403
curl -s -o /dev/null -w '%{http_code}\n' \
  'http://127.0.0.1:18080/api/fetch_source.php%3Fa.php?url=http://example.org/'
# 200
```

The same pair on the live instance gives 403 and then 400 with the body
`{"error":"only http(s) sources"}`, which is the script rejecting the URL rather than
Apache rejecting the caller, so the bypass reproduces on the deployment.

A later measurement made this cheaper than it first looked. Unlike `keyring.php` and
`vault_unseal.php`, `peer_probe.php`, and `webhook_test.php` omit the PHP-level check on `REMOTE_ADDR`.
Stage A alone reaches them from outside in one request each. That
gave two extra primitives that never ended up paying. `peer_probe` reflects
`$j['version'] ?? $j['node']` of any JSON it fetches through a `^[\w.\-]{1,32}$` filter,
and `webhook_test` returns the exact byte length of any loopback response, which is the
only way in the whole application to send a POST to a gated script.

## Stage B: make fetch_source return a body

`fetch_source.php` sets `follow_location => 1` explicitly in its stream context. The PHP
http wrapper only follows a 3xx by default, but an explicit context option overrides that
in `ext/standard/http_fopen_wrapper.c`, so it follows a `Location` header on any status
whatsoever. The script separately flags a chain as unusual when any status in it falls
outside `[200, 204, 301, 302, 303, 307, 308]`, and an unusual chain makes it dump the
final response body into its JSON `trace` field.

Put those together and the redirector is nine lines, answering every request with
`418 Teapot` plus `Location: <target>`. That is `solve/redir.py`, and it wants a public
origin in front of it. The tunnel turned out to be unnecessary:

```
https://httpbin.org/redirect-to?url=<urlencoded target>&status_code=309
```

309 is a 3xx, so httpbin will emit it, and 309 is not in the standard list, so the chain
is flagged unusual and the body comes back. `solve/solve.py --redir` accepts that form
with a `{URL}` placeholder.

A non-200 loopback body omits the redirector. The first hop already yields
the unusual status:

```bash
curl -s "$BASE/api/fetch_source.php%3Fa.php?url=http%3A%2F%2F127.0.0.1%2Fapi%2Fvault_unseal.php"
# chain [409], trace {"error":"unseal handshake not established for this peer"}
```

Through the redirector, `http://127.0.0.1/api/keyring.php` returns the appliance keyring
(`artifacts/keyring.json`). It holds the restore session ids that `restore.php?job=`
requires, plus an `unseal_ref`. Feeding that ref back through the same SSRF to
`/api/vault_unseal.php?ref=<ref>` returns `cap_key_masked`
(`artifacts/vault_unseal.json`), base64 of `cap_key XOR cap.mask`.

## Stage C: the missing build

`cap.mask` is read in exactly three places, and only one of them faces an attacker, since
`render_template.php` puts it into the renderer context as `config.cap_mask` whenever the
`event` field matches `/^maintenance\./`. In the handout it is protected by a taint flag
and prints as `[redacted]`, and the intended leak is an exception rather than a value,
since `{{1/(ord(substr(config.cap_mask,0,1))-N)}}` raises `DivisionByZeroError` and turns
the whole response into HTTP 500. That is `leak_mask()` in the solve script, it works
against a local container built from the handout, and the deployment lacks it.

The deployed renderer is a different engine, and reverse engineering it black-box took one
useful trick and a lot of requests that were not needed. Its delimiter is `[[ ]]`, its
grammar is `[[path|filter:arg|filter:arg]]`, and an unknown filter name makes it echo the
whole span back verbatim, which is a free existence oracle over the filter dictionary. The
trick is batching, because every span in a template renders independently and the field
holds about 2000 characters, so one request answers 40 to 90 questions when each span is
tagged with a `~N~` marker and parsed back out. `solve/probe_taint.py` does the packing,
the marker parsing, and the retry in smaller chunks on a truncated template. An earlier
sweep that spent one request per name needed five requests and used 250, and the resulting
traffic knocked our connection over twice.

What the sweep found, measured on the live instance and saved in
`artifacts/probe_taint/characterize.json`, looks unpromising. Eleven filters exist
(`upper lower len trim slice sub at char mul add code`), every one of them casts its
subject so none of them can throw, arguments are literals that do not resolve context
paths (`[[node|add:config.retention_days]]` renders `0`, not `30`), the taint rides the
value through a chain of ten filters and is never recomputed, every parse error renders
the empty string at HTTP 200, and 250 further filter names all echo. The handout's oracle
had been removed precisely, since the deployed set drops `/` and renames `ord` to `code`.

Four parallel sessions independently refuted that reading. The write-up of a
wrong conclusion is worth more than the conclusion itself. The reasoning is preserved in
`NOTES.md`. The error was upstream of all of it. Asked whether we had the re-uploaded zip,
we had not:

```bash
md5sum handout/vaultkeeper-source.zip            # local, fetched 10:14
# fe97e96f46cc5184a8130848ed7a1621    98621 bytes
curl -sO "$(jq -r '.files[0].url' meta.json)"
md5sum vaultkeeper-source.zip                    # served 17:00
# 5864c94820bbecc189095a62800b5f86   101623 bytes
```

Same URL, same hash suffix in the filename, different content. The current build adds
`src/public/api/vault_unseal.php` and `src/lib/recovery.php`, changes `keyring.php`,
`render_template.php`, `util.php`, `tokens.php`, and `restore.php`, and adds a twelfth
filter at `render_template.php:113`:

```php
case 'bar':  return new VkField(str_repeat((string) ($a[0] ?? "\u{2588}"), (int) $in->v), $p);
```

The comparison operator the ledger recorded as deleted had been re-added in a shape nobody
recognized. The standing rule this earns is to compare handout content rather than the
handout URL whenever a challenge resists for hours; across the whole event two files were
stale this way, and the other one was already solved.

Two controls go first, and neither touches a secret, because `seed()` accepts a literal
integer as `#-?\d+`:

```
[[#-1|bar]]    -> the span echoed verbatim   (the throw reaches the catch)
[[#0|bar]]     -> ""                          (no throw, empty repeat)
[[#5|bar:x]]   -> "xxxxx"                     (the filter is reachable)
```

The live run forced one correction on the recipe as first drafted. The oracle
is the body rather than the status code. `VkPipeline::render()` wraps each span in a try/catch and
answers HTTP 200 either way.

## Stages D through G: from cap_key to a shell

With the mask out, `cap_key = b64d(cap_key_masked) XOR mask`, and it can be checked
offline before a single further request is spent. `/api/status.php` publishes
`read_capability`, which is `vk_cap_issue('viewer')`. Decrypting it as AES-128-GCM with
nonce `raw[:12]`, ciphertext `raw[12:28]`, and tag `raw[28:44]` must yield exactly
`b'viewer          '`. That verifier is `verify_cap_key()` in the solve script. It scored
every mask hypothesis tried during the long middle.

With `cap_key` in hand, the rest follows. Capabilities are forgeable, so `vk_cap_issue('maintainer')`
opens `import_db`. The seal key is `hash_hmac('sha256', 'vk-checkpoint-seal.v4', cap_key, true)`,
and the resume envelope key is `hash_hmac('sha256', 'vk-resume-envelope.v2', cap_key, true)`.
Session ids are `HMAC(HMAC(cap_key, 'vk-restore-session.v2'), "sec|usec|seq")` truncated to
24 hex. The keyring already returned those at stage B.

Stage E is the interpolated table name. A bundle whose `database.sql` creates a table
called `<rand>`;UPDATE vaultkeeper.jobs SET role='operator';#` reaches the `DROP TABLE`
above on the `vk_app` connection, which has `MULTI_STATEMENTS` enabled and write access to
the main database, and flips the job's role. The random prefix matters, because the
injected `DROP` only removes the short prefix table and a fixed name collides on the
second run.

Stage F is the deserialization. `system_restore` unserializes the tar member `state.dat`
after restricting `allowed_classes`, behind an envelope the current build added:
`"VKR2" | HMAC-SHA256(payload, ckpt_key)[32 raw] | payload`. The chain inside is:

```
RestorePoint::__unserialize      (HMAC gate, key derived from cap_key)
  -> __destruct                  $sink[$slot] = $snapshot
    -> CacheShard::offsetSet     casts $reconcile to string
      -> DocFragment::__toString
        -> PartialLoader::render
          -> ManifestCursor::current
            -> call_user_func_array($spec['stage'], $spec['args'])
```

`build_state_dat()` emits it by hand as PHP serialization bytes, `frame_resume()` adds the
envelope. The `--legacy-state` flag emits the bare pre-VKR2 blob for the old build. The console
is `restore.php?job=<session_id>`, screenshotted at `artifacts/shots/02-restore-console.png`.

## Dead ends

Hash length extension looked deliberate and was real. `entrypoint.sh` randomizes the token
secret length to 28 through 40 bytes, which reads as a planted hint, and
`vk_ticket_tag = sha256(secret . http_build_query(claims))` genuinely extends. Brute-forcing
the thirteen candidate lengths against `GET /api/session_ticket.php?ticket=` found the
secret at 32 bytes. The forged ticket is still useless, because `vk_ticket_verify` parses
with `parse_str`, PHP's `parse_str` runs `strtok` over a C string, and the NUL bytes in the
SHA-256 glue padding truncate the parameter list before the appended `&scope=admin` is ever
read.

Skipping the HMAC gate does not work either. `unserialize` enforces declared property
types, and `VkSealContext::$slot` and `::$mac` are both `readonly string`, so a
`DocFragment` cannot be swapped in to fire `__toString` ahead of the seal check.
`VkProgressMeter::__destruct` is empty. `VkHookRegistry::__wakeup` casts nothing.
`RestorePoint` is the only reachable destructor.

Guessing or deriving the mask is impossible. `entrypoint.sh` shows both `cap.key` and `cap.mask` are independent
`head -c N /dev/urandom | base64 | tr -d '=+/\n' | head -c 16` reads generated inside the
container at first boot, giving sixteen uniform characters of `[A-Za-z0-9]` each and a
residual keyspace near 2^85 for `masked = key XOR mask`. Roughly 3,800 derivations from
`unseal_ref`, the node name, the slot, the deployment name, and every library constant, in
raw, hex, md5, sha1, and sha256 forms, all went through the GCM verifier, and then through
a weaker scorer that only demands sixteen alphanumeric characters out of the XOR, in case
the verifier itself was wrong. No hit either way.

`query.php` is a real multi-statement SQL injection. It yields nothing. The
`vk_restore` user holds `USAGE` only outside its own database and lacks the `FILE` privilege.
`secure_file_priv` is `/var/lib/mysql-files`. `SELECT ... FROM vaultkeeper.jobs` returns
error 1142, and PDO blocks `LOAD DATA LOCAL INFILE` client-side.

`util.php` declares `const VK_CAP_IV` and never uses it. An unused fixed nonce declared in
a library has the shape of a planted nonce reuse, so the constant earned 16 capability
samples pulled from `/api/status.php` and `/api/request_restore.php`. All 16 nonces are
distinct, no byte position is constant, and the planted constant never appears, so the
deployed build calls `random_bytes(12)` like the handout does. The GCM forbidden attack is
nevertheless built and self-tested in `solve/gcm.py`, ready for the day a nonce collision
does turn up.

Pointing the deployed `peer_probe` and `webhook_test` at a rogue peer we controlled
refuted the cluster-handshake hypothesis. `peer_probe` sends a bare GET including only
`Host` and `Accept-Encoding`. `webhook_test` sends the handout's
`vk_webhook_sample_payload` byte for byte. It omits the signature header. Neither leaks
anything outbound.

Three smaller negatives, each cheap. PHP's http wrapper skips
a `Location` that points to a different scheme. `file://`, `php://filter`, `data:`, and
`gopher://` all loop back to the attacker origin instead of reading a file. php-fpm's
`security.limit_extensions` still executes `.phar`. That would matter if the
application wrote into the docroot. The application avoids that. The dotted-path idea
`[[config.cap_mask.0]]` renders the empty string, because `seed()` guards its walk with
`is_array($v) && array_key_exists($k, $v)` and a string is not an array.

## Reproduce

```bash
ctf-python solve/solve.py \
  --base http://<deployment>.challs.ctf.thefewchosen.com \
  --redir 'https://httpbin.org/redirect-to?url={URL}&status_code=309'
```

No `--mask` argument is needed, since the `bar` oracle recovers it. The script runs stages
A through G unattended in about two minutes, and it was verified twice on the live instance
plus twice on a local container built from `handout/src-current`. The live run
recovered mask `EocUoRER21zfvzC7` and cap key `QFNnDN10wlF7LKeP`. Evidence sits in
`artifacts/keyring.json`, `artifacts/vault_unseal.json`, `artifacts/import_db.html`,
`artifacts/system_restore.html`, `artifacts/remote-evidence.txt`, and
`artifacts/shots/03-solve-run.png`.

Flag: `TFC{04d4c11ea3641f2ec562b657ea6428b4}`

</details>
