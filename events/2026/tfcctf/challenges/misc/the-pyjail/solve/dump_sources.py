"""
Run INSIDE the jail container. Dump every int and str value reachable by an
expression written only with [a-z_.\\[\\],:] starting from `sys`, plus the os
module reached through sys.modules. Output is python-literal-ish lines that the
payload builder consumes.
"""
import sys
import json
import re

NAME = re.compile(r'^[a-z_][a-z_]*$')
BAD = ('ass', 'typ', 'als')


def ok(n):
    return bool(NAME.match(n)) and not any(b in n for b in BAD)


ints = {}
strs = {}
seen = set()


def walk(path, obj, d):
    if d > 3:
        return
    key = (id(obj), path.count('.'))
    if id(obj) in seen and d > 1:
        return
    seen.add(id(obj))
    try:
        names = dir(obj)
    except Exception:
        return
    for n in names:
        if not ok(n) and n not in ('__name__', '__doc__', '__qualname__',
                                   '__module__', '__file__'):
            continue
        if any(b in n for b in BAD):
            continue
        try:
            v = getattr(obj, n)
        except Exception:
            continue
        p = path + '.' + n
        if isinstance(v, bool):
            ints.setdefault(int(v), p)
        elif isinstance(v, int):
            if 0 <= v < 4000:
                ints.setdefault(v, p)
        elif isinstance(v, str):
            if v and len(v) < 30000:
                strs.setdefault(p, v)
        elif isinstance(v, tuple):
            for i, e in enumerate(v):
                if isinstance(e, str):
                    strs.setdefault('%s[IDX%d]' % (p, i), e)
        elif isinstance(v, list):
            for i, e in enumerate(v):
                if isinstance(e, str):
                    strs.setdefault('%s[IDX%d]' % (p, i), e)
        elif callable(v) or hasattr(v, '__dict__'):
            walk(p, v, d + 1)


walk('sys', sys, 0)
o = sys.modules['os']
walk('OS', o, 0)

print(json.dumps({'ints': {str(k): v for k, v in ints.items()},
                  'strs': strs}))
