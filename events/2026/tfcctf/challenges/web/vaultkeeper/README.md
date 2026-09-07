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
<summary><b>My Solution</b></summary>

The organizers rated this difficult "baby" but it was pretty hard grr. It's PHP 8.2 behind Apache 2.4.56, pinned so hard the entrypoint aborts if the version differs, with php-fpm over `SetHandler proxy:fcgi`. `apache/vaultkeeper.conf` restricts `fetch_source`, `peer_probe`, `webhook_test`, and `keyring.php` to `Require ip 127.0.0.1`. A pinned 2.4.56 plus a `FilesMatch` ACL plus mod_proxy is a very loud hint at [CVE-2024-38473](https://nvd.nist.gov/vuln/detail/CVE-2024-38473), and sure enough `GET /api/fetch_source.php%3Fa.php` returns 200 and runs the script where the plain path is 403. `FilesMatch` matches the basename `fetch_source.php?a.php`, which doesn't match the pattern, and then mod_proxy truncates at the `?` so php-fpm runs it anyway.

Now you have an SSRF, and `fetch_source.php` sets `follow_location=1` explicitly so PHP follows a `Location` header on any status. Serve a 418 with `Location: http://127.0.0.1/api/keyring.php` and the unusual status makes the endpoint dump the final body into its `trace` field. The handout's keyring leaks `cap_key_masked` directly, but the deployed one doesn't. It returns an `unseal_ref` pointing at `/api/vault_unseal.php`. That endpoint isn't in the handout and is instead loopback-gated in PHP, so reach it through the same SSRF.

Getting the mask is where the deployed build really diverges. `cap_key = b64d(cap_key_masked) XOR mask`, and the mask is tainted and prints as `[redacted]`. In the handout you pull it out with a division by zero, since `1/(ord(substr(config.cap_mask,0,1))-N)` throws and gives you HTTP 500 versus 200, a byte oracle in about a hundred requests. The deployed renderer is a different engine though:
- it uses `[[ ]]` not `{{ }}`, and it's a filter engine, `[[path|filter:arg:arg]]` with args as raw strings
- an unknown filter name makes it echo the whole `[[...]]` back verbatim, which is a clean existence oracle, so you can enumerate the whole set: `upper lower len trim slice sub at char mul add`
- the handout's set was `strlen substr ord chr upper lower int` plus `+ - * /`, so the deployed build drops `/` and drops `ord`, which are precisely the two things the handout oracle needs
- taint propagates through every filter too, so `|len` and `|at:0` on the mask still render `[redacted]`

What worked came from the re-uploaded handout, which has one more filter, `bar`. `str_repeat` raises a `ValueError` on a negative count and the per-span catch echoes that span verbatim at HTTP 200, so it's the same oracle shape with a different exception.

With `cap_key` in hand the rest falls over. `vk_seal_key = hash_hmac('sha256','vk-checkpoint-seal.v4',cap_key,true)`, so `vk_cap_issue('maintainer')` is forgeable. Then `import_db` interpolates table names created in `vk_restore` straight into a DROP, run as `vk_app` on the main database with `MULTI_STATEMENTS` on:
```sql
DROP TABLE IF EXISTS `vk_restore`.`$name`
```
So a backtick in the name is SQLi and you can `UPDATE jobs SET role='operator'`. Make the injected name unique per run so the injected DROP only removes the short prefix table. Finally `system_restore` unserializes the tar member `state.dat` with no `allowed_classes`:
```
RestorePoint::__unserialize      (HMAC gate, key from the seal)
  -> __destruct                  $sink[$slot] = $snapshot
    -> CacheShard::offsetSet     casts $reconcile to string
      -> DocFragment::__toString
        -> PartialLoader::render
          -> ManifestCursor::current
            -> call_user_func_array($spec['stage'], $spec['args'])
```
`restore.php` wants `?job=<session_id>`, which keyring already leaked for you way back at the SSRF step. The whole thing runs unattended, and you don't need a tunnel since httpbin will serve the 309 for you.

## Other stuff I tried

Things that looked like a way in:
- hash length extension. `entrypoint.sh` randomises the token secret length, which reads like a deliberate hint, and `vk_ticket_tag = sha256(secret . http_build_query(claims))` really is extendable. I brute-forced the candidate lengths and found the secret. The forged ticket is useless though, because `vk_ticket_verify` uses `parse_str`, and PHP `parse_str` runs `strtok` over a C string, so the NUL bytes in the SHA-256 glue padding truncate the parameters before your appended `&scope=admin` is ever parsed
- a shortcut into the POP chain. `unserialize` enforces declared property types, and on `VkSealContext` both `$slot` and `$mac` are `readonly string`, so you can't swap in a `DocFragment` to fire `__toString` before the HMAC check. RCE genuinely needs `vk_seal_key`, so there's no way round the mask oracle
- `query.php`, a real multi-statement SQLi as `vk_restore`, except that user has `USAGE` only outside its own database, no `FILE`, and PDO blocks `LOAD DATA LOCAL INFILE` client-side
- guessing the mask from `unseal_ref` as hex, md5, sha1, sha256, or raw, all of which fail. Cheap to try though, since a guess costs no requests: decrypt `read_capability` from `/api/status.php` with a candidate key and the plaintext has to be `'viewer          '`

Flag: `TFC{04d4c11ea3641f2ec562b657ea6428b4}`
</details>
