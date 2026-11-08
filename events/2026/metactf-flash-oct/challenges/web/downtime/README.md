# Downtime

| | |
|---|---|
| Event | MetaCTF October 2026 Flash CTF |
| Category | web |
| Points | 400 |
| Solves at capture | 3 |
| Status | partial |

> The maintenance window was supposed to last an hour, but a week has passed and we're still not back online...
>
> Service HTTPS.
>
> Handout: downtime.zip

Files: [`downtime.zip`](handout/downtime.zip)

I didn't finish this one. The chunked out-of-memory crash works on the live target, but I never calibrated the heap leak for this PHP build.

<details>
<summary><b>Solution (partial)</b></summary>

PHP 8.2.34's out-of-memory handler longjmps out of multipart parsing before any application code runs. That same PHP serves the maintenance page, so the page can't guard against the crash.

## Recon

The app, `index.php`, prints a fixed 503 maintenance page. Its footer shows `PHP_VERSION`, 8.2.34, the last vulnerable 8.2 release. The Dockerfile pins `php:8.2.34-apache-bookworm` with one prefork worker (`MaxRequestWorkers 1`).

## php2shell (CVE-2026-109618)

Exhausting `memory_limit` inside rfc1867 multipart parsing makes the handler longjmp out. mod_php then runs request shutdown over half-built request and session state. A single prefork worker serves every request, so the leftover heap repeats between requests (the leak-then-reclaim chain needs that).

## The foothold

The config sets `memory_limit=128M` and `post_max_size=8M`, so a body over 8M with a Content-Length gets refused. A chunked multipart POST omits the Content-Length, so `post_max_size` doesn't apply and the parser allocates past 128M. With `display_errors=On`, the worker answers 200 with the fatal error in the body: "Allowed memory size of 134217728 bytes exhausted in Unknown on line 0." The error fires in the SAPI, before the 503 app code.

## What's left

The OOM leaves the session id pointer `PS(id)` dangling. A second request reclaims that slot with a forged `zend_string`. An oversized `Set-Cookie` then over-reads the heap to leak the Zend memory base and libc. A third request forges a `HashTable` with its destructor set to `zif_system` and runs `system('cat /flag.txt')`.

The leak didn't reproduce. The public chain targets the PHP 8.3 and later allocator at an 8M `memory_limit`, and the 8.2 heap after a 128M OOM looks different. The filler field count and sizes need re-tuning for it.

The public php2shell tool reports "stage 1 never leaks" on 8.2, but it ran on 8.2.35, the patched build. SkillBit's [official writeup](https://skillbit.com/blogs/flash-ctf-downtime) confirms 8.2.34 is exploitable, but says the public chain doesn't carry over and outlines a different four-stage route.

## Reproduce

    CTF_LOCAL=1 ctf-python solve/solve.py

The script fires the chunked OOM at a replica built from the handout, or at the target. The leak and reclaim stages are scaffolding, so it prints no flag.

</details>
