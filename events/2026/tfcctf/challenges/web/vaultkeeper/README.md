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

The template renderer holds the secret mask (the file `/var/www/private/cap.mask`, exposed as `config.cap_mask`) but prints it as `[redacted]`. Its `bar` filter is `str_repeat`, which throws on a negative count, and a span that throws comes back verbatim. That turns every mask character into a comparison, and the mask unlocks everything else.

```
POST /api/render_template.php
{"event":"maintenance.x","template":"[[config.cap_mask|at:0|code|sub:200|bar:.]]"}
```

This renders `[redacted]` when `ord(mask[0]) >= 200` and echoes the span when it doesn't. Binary search settles a character in about seven probes, so about 112 requests recover all sixteen. Both responses are in `artifacts/remote-evidence.txt`.

## Recon

The Dockerfile pins `php:8.2.12-apache-bullseye` by digest and runs `apt-mark hold apache2 apache2-bin apache2-data`. `entrypoint.sh` aborts unless `apache2 -v` reports exactly 2.4.56. The pin keeps a known Apache bug alive, and the config shows which one:

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

An ACL keyed on a basename, `SetHandler proxy:fcgi`, and Apache 2.4.56 are the preconditions for [CVE-2024-38473](https://nvd.nist.gov/vuln/detail/CVE-2024-38473), one of Orange Tsai's confusion attacks.

`FilesMatch` sees the decoded basename, so `fetch_source.php%3Fa.php` becomes `fetch_source.php?a.php` and the `Require ip` never applies. mod_proxy then cuts the FastCGI path at the `?`, so php-fpm gets `SCRIPT_FILENAME=/var/www/html/public/api/fetch_source.php` and runs it anyway.

At the far end, `unserialize(` lands in `src/lib/restore_state.php`, where `RestorePoint::__unserialize` leads to a `__destruct` that writes through `ArrayAccess`. The only interpolated SQL is a table name in `vk_import_database`:

```php
$pdo->exec("DROP TABLE IF EXISTS `vk_restore`.`$name`");
```

Both sit behind a key called `cap_key`. Stages A through D recover it.

## Stage A: the ACL bypass

I built the Docker image from the 10:14 handout (the STALE-1014 zip) and ran it on port 18080 with the fake flag `TFC{local_test_do_not_submit}`.

```bash
curl -s -o /dev/null -w '%{http_code}\n' http://127.0.0.1:18080/api/fetch_source.php
# 403
curl -s -o /dev/null -w '%{http_code}\n' \
  'http://127.0.0.1:18080/api/fetch_source.php%3Fa.php?url=http://example.org/'
# 200
```

On the live instance the bypass gets 400 with `{"error":"only http(s) sources"}`. That's the script rejecting the URL, not Apache rejecting the caller.

## Stage B: make fetch_source return a body

`fetch_source.php` sets `follow_location => 1` explicitly. Without that option, PHP follows a Location header only on 300, 301, 302, 303, 307, and 308. Setting it to 1 makes PHP follow one on any status, as the PHP manual page on HTTP context options says. The script dumps the final body into its JSON `trace` field when a status in the chain falls outside `[200, 204, 301, 302, 303, 307, 308]`.

`solve/redir.py` answers every request with `418 Teapot` plus `Location: <target>`, but it needs a public address. httpbin does the same job without one:

```
https://httpbin.org/redirect-to?url=<urlencoded target>&status_code=309
```

httpbin emits any 3xx code it's asked for. 309 is outside the list, so the body comes back. `solve/solve.py --redir` takes that form with a `{URL}` placeholder. A loopback script that answers with a status outside that list doesn't need the redirector at all:

```bash
curl -s "$BASE/api/fetch_source.php%3Fa.php?url=http%3A%2F%2F127.0.0.1%2Fapi%2Fvault_unseal.php"
# chain [409], trace {"error":"unseal handshake not established for this peer"}
```

Through the redirector, `http://127.0.0.1/api/keyring.php` returns the keyring (`artifacts/keyring.json`). It holds the session ids that `restore.php?job=` requires, plus an `unseal_ref`. Sending that ref to `/api/vault_unseal.php?ref=<ref>` returns `cap_key_masked` (`artifacts/vault_unseal.json`), base64 of `cap_key XOR cap.mask`.

## Stage C: the mask

`render_template.php` puts the mask into the renderer as `config.cap_mask` whenever `event` matches `/^maintenance\./`, behind a taint flag. The grammar is `[[path|filter:arg|filter:arg]]`, and `VkPipeline::render()` catches a throw per span and returns that span verbatim at HTTP 200. So the oracle has to read the body. Here's the filter, at `render_template.php:113`:

```php
case 'bar':  return new VkField(str_repeat((string) ($a[0] ?? "\u{2588}"), (int) $in->v), $p);
```

The controls use literals instead of the secret, because `seed()` accepts a literal integer as `#-?\d+`:

```
[[#-1|bar]]    -> the span echoed verbatim   (the throw reaches the catch)
[[#0|bar]]     -> ""                          (no throw, empty repeat)
[[#5|bar:x]]   -> "xxxxx"                     (the filter is reachable)
```

The organizers replaced the zip at the same URL mid-event, and the copy I worked from for hours lacks `bar`. Its renderer is an older engine that leaks through `DivisionByZeroError` instead (`leak_mask()` in the solve script). Black-box probing the deployed engine found eleven filters, none of which can throw, and I wrongly concluded the oracle was gone:

```bash
md5sum handout/vaultkeeper-source.zip            # local, fetched 10:14
# fe97e96f46cc5184a8130848ed7a1621    98621 bytes
curl -sO "$(jq -r '.files[0].url' meta.json)"
md5sum vaultkeeper-source.zip                    # served 17:00
# 5864c94820bbecc189095a62800b5f86   101623 bytes
```

The current build also adds `src/public/api/vault_unseal.php` and `src/lib/recovery.php`. The 10:14 copy is now the STALE-1014 zip in `handout/`, and `handout/vaultkeeper-source.zip` is the 17:00 copy.

## Stages D through G: from cap_key to a shell

Stage D computes `cap_key = b64d(cap_key_masked) XOR mask`, and I can check the result offline. `/api/status.php` publishes `read_capability`, which is `vk_cap_issue('viewer')`. Decrypting it as AES-128-GCM with nonce `raw[:12]`, ciphertext `raw[12:28]`, and tag `raw[28:44]` must give `b'viewer          '`, as `verify_cap_key()` checks.

With `cap_key`, capabilities are forgeable, so `vk_cap_issue('maintainer')` opens `import_db`. The seal key `vk_seal_key()` is `hash_hmac('sha256', 'vk-checkpoint-seal.v4', cap_key, true)`, and it gates `RestorePoint` below. The resume envelope key `vk_ckpt_key()` is `hash_hmac('sha256', 'vk-resume-envelope.v2', cap_key, true)`, the `ckpt_key` that signs the envelope.

Stage E is the table name. The bundle's `database.sql` creates a table whose name closes the quoting and appends an UPDATE that makes the job an operator. The `vk_app` connection runs the `DROP TABLE` above with `MULTI_STATEMENTS` enabled and write access to the main database, so the UPDATE lands. The solve gives the table name a random prefix, so a rerun doesn't collide with the last run's table.

Stage F is the deserialization. `system_restore` unserializes the tar member `state.dat` with restricted `allowed_classes`, inside the envelope `"VKR2" | HMAC-SHA256(payload, ckpt_key)[32 raw] | payload`:

```
RestorePoint::__unserialize      (HMAC gate, key derived from cap_key)
  -> __destruct                  $sink[$slot] = $snapshot
    -> CacheShard::offsetSet     casts $reconcile to string
      -> DocFragment::__toString
        -> PartialLoader::render
          -> ManifestCursor::current
            -> call_user_func_array($spec['stage'], $spec['args'])
```

`build_state_dat()` writes the PHP serialization bytes by hand, and `frame_resume()` adds the envelope. The `--legacy-state` flag skips the envelope for the old build. The console is `restore.php?job=<session_id>`.

## Reproduce

Run `solve/solve.py` with `--base` set to the instance URL and `--redir 'https://httpbin.org/redirect-to?url={URL}&status_code=309'`. The `bar` oracle recovers the mask, so `--mask` is optional, and the script runs stages A through G unattended. The live run recovered cap key `QFNnDN10wlF7LKeP`. Evidence sits in `artifacts/keyring.json`, `artifacts/vault_unseal.json`, `artifacts/import_db.html`, `artifacts/system_restore.html`, `artifacts/remote-evidence.txt`, and `artifacts/shots/03-solve-run.png`.

Flag: `TFC{04d4c11ea3641f2ec562b657ea6428b4}`

</details>
