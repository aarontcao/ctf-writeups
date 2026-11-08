"""Helpers shared by the solve scripts. `import ctf` works under `ctf-python`,
which puts this directory on PYTHONPATH, and the templates walk up to find it.
"""

from __future__ import annotations

import json
import os
import pathlib
import re
import subprocess
import sys

DEFAULT_FLAG_RE = r"[A-Za-z0-9_]{3,15}\{[^}\n]{1,256}\}"


# --- locating things ---


def challenge_dir(start: str | None = None) -> pathlib.Path:
    """The nearest directory above the calling script that holds meta.json."""
    p = pathlib.Path(start or sys.argv[0]).resolve()
    if p.is_file():
        p = p.parent
    for cand in [p, *p.parents]:
        if (cand / "meta.json").is_file():
            return cand
    return p


def meta(start: str | None = None) -> dict:
    d = challenge_dir(start)
    f = d / "meta.json"
    return json.loads(f.read_text()) if f.is_file() else {}


def artifact(name: str, start: str | None = None) -> pathlib.Path:
    """Path under artifacts/"""
    d = challenge_dir(start) / "artifacts"
    d.mkdir(parents=True, exist_ok=True)
    return d / name


def scratch(name: str, start: str | None = None) -> pathlib.Path:
    """Path under scratch/, which is gitignored."""
    d = challenge_dir(start) / "scratch"
    d.mkdir(parents=True, exist_ok=True)
    return d / name


def handout(name: str, start: str | None = None) -> pathlib.Path:
    return challenge_dir(start) / "handout" / name


# --- connection ---


def parse_connection(s: str) -> dict:
    """Parse `nc host port`, `ncat --ssl host port`, `host:port`, or an http(s) URL."""
    s = (s or "").strip()
    if not s:
        return {}
    if s.startswith("http://") or s.startswith("https://"):
        return {"kind": "http", "url": s}
    ssl = bool(re.search(r"--ssl|\bssl\b", s))
    m = re.search(r"([\w.\-]+)\s+(\d{2,5})\s*$", s)
    if m:
        return {"kind": "tcp", "host": m.group(1), "port": int(m.group(2)), "ssl": ssl}
    m = re.search(r"([\w.\-]+):(\d{2,5})", s)
    if m:
        return {"kind": "tcp", "host": m.group(1), "port": int(m.group(2)), "ssl": ssl}
    return {"kind": "unknown", "raw": s}


def target(start: str | None = None) -> dict:
    """The meta.json connection, or CTF_TARGET if set, for when an instance moves."""
    override = os.environ.get("CTF_TARGET")
    if override:
        return parse_connection(override)
    return parse_connection(meta(start).get("connection", ""))


def tube(local: str | None = None, start: str | None = None, **kw):
    """A pwntools tube to the remote, or to `local` when CTF_LOCAL is set."""
    from pwn import process, remote  # imported late so `import ctf` stays cheap

    if os.environ.get("CTF_LOCAL") and local:
        return process(local, **kw)
    t = target(start)
    if t.get("kind") != "tcp":
        raise RuntimeError(f"no tcp target in meta.json (got {t!r}); set CTF_TARGET")
    return remote(t["host"], t["port"], ssl=t.get("ssl", False), **kw)


# --- flags ---


def flag_re(start: str | None = None) -> re.Pattern:
    """The flag regex from the nearest event.json, else DEFAULT_FLAG_RE."""
    d = challenge_dir(start)
    for cand in [d, *d.parents]:
        f = cand / "event.json"
        if f.is_file():
            try:
                pat = json.loads(f.read_text()).get("flag_regex")
            except (OSError, ValueError):
                pat = None
            if pat:
                return re.compile(pat)
            break
    return re.compile(DEFAULT_FLAG_RE)


def find_flag(blob, start: str | None = None) -> str | None:
    """Pull a flag out of a blob with the event regex, then the default one."""
    if isinstance(blob, bytes):
        blob = blob.decode("utf-8", "replace")
    m = flag_re(start).search(blob)
    if m:
        return m.group(0)
    m = re.search(DEFAULT_FLAG_RE, blob)
    return m.group(0) if m else None


def record(flag: str, slug: str | None = None) -> None:
    """Record a flag through the CLI."""
    slug = slug or challenge_dir().name
    subprocess.run([os.path.expanduser("~/.ctf/bin/ctf"), "flag", slug, flag], check=False)


def win(blob, slug: str | None = None) -> str | None:
    """Find a flag in a blob, then print and record it."""
    f = find_flag(blob)
    if f:
        print(f"\n[+] FLAG: {f}")
        record(f, slug)
    else:
        print("\n[-] no flag in that output")
    return f


# --- small conveniences ---


def xor(a: bytes, b: bytes) -> bytes:
    """Repeating-key xor of a with b."""
    if not b:
        raise ValueError("empty key")
    return bytes(x ^ b[i % len(b)] for i, x in enumerate(a))


def chunks(data, n: int):
    return [data[i : i + n] for i in range(0, len(data), n)]


def transcript(name: str = "session.txt", start: str | None = None):
    """Open an artifacts/ log file for a hand-written transcript."""
    return open(artifact(name, start), "a", encoding="utf-8")
