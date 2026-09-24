"""
Dump reachable int and str values with their access expressions.
"""
import sys, json, re
NAME = re.compile(r'^[a-z_][a-z_0-9]*$')
BAD = ('ass', 'typ', 'als')
DUN = ('__name__', '__doc__', '__qualname__', '__module__', '__file__')

def ok(n):
    if any(b in n for b in BAD):
        return False
    if n in DUN:
        return True
    return bool(NAME.match(n)) and not any(c.isdigit() for c in n)

ints = {}
strs = {}
seen = set()

def walk(path, obj, d, maxd):
    if d > maxd or id(obj) in seen:
        return
    seen.add(id(obj))
    try:
        names = dir(obj)
    except Exception:
        return
    for n in names:
        if not ok(n):
            continue
        try:
            v = getattr(obj, n)
        except Exception:
            continue
        p = path + '.' + n
        if isinstance(v, bool):
            ints.setdefault(int(v), []).append(p)
        elif isinstance(v, int):
            if 0 <= v <= 200:
                ints.setdefault(v, []).append(p)
        elif isinstance(v, str):
            if v:
                strs.setdefault(p, v)
        elif isinstance(v, (tuple, list)):
            for i, e in enumerate(v):
                if isinstance(e, str) and e:
                    strs.setdefault('%s[IDX%d]' % (p, i), e)
            walk(p, v, d + 1, maxd)   # structseq named fields
        else:
            walk(p, v, d + 1, maxd)

walk('sys', sys, 0, 3)
sysints = {k: list(v) for k, v in ints.items()}
sysstrs = dict(strs)
o = sys.modules['os']
seen.clear()
walk('sys.q', o, 0, 3)
print(json.dumps({'sysints': sysints, 'sysstrs': sysstrs,
                  'allints': {k: v for k, v in ints.items()},
                  'allstrs': strs,
                  'bmn': list(sys.builtin_module_names)}))
