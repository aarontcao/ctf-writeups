"""
BFS the object graph reachable from sys with lowercase+underscore attribute
names only, hunting for a call primitive: a Python-level __getitem__, a Python
property, or a module __getattr__.
"""
import sys
import types
import re

NAME = re.compile(r'^[a-z_]+$')
BAD = ('ass', 'typ', 'als')


def ok_name(n):
    return bool(NAME.match(n)) and not any(b in n for b in BAD)


seen = set()
found = []
queue = [('sys', sys)]
depth = {'sys': 0}
MAXDEPTH = 4

while queue:
    path, obj = queue.pop(0)
    d = depth[path]
    if d > MAXDEPTH:
        continue
    try:
        oid = id(obj)
    except Exception:
        continue
    if oid in seen:
        continue
    seen.add(oid)

    t = type(obj)
    # 1. python-level __getitem__
    gi = getattr(t, '__getitem__', None)
    if isinstance(gi, (types.FunctionType, types.MethodType)):
        found.append(('GETITEM', path, t.__name__, getattr(gi, '__qualname__', '?')))
    # 2. module __getattr__
    if isinstance(obj, types.ModuleType):
        ga = obj.__dict__.get('__getattr__')
        if ga is not None:
            found.append(('MODGETATTR', path, obj.__name__, repr(ga)[:80]))
    # 3. class-level __getattr__ implemented in python
    ga2 = getattr(t, '__getattr__', None)
    if isinstance(ga2, types.FunctionType):
        found.append(('GETATTR', path, t.__name__, getattr(ga2, '__qualname__', '?')))

    try:
        names = dir(obj)
    except Exception:
        continue
    for n in names:
        if not ok_name(n):
            continue
        # property / descriptor implemented in python -> attribute access is a call
        try:
            desc = getattr(t, n, None)
        except Exception:
            desc = None
        if isinstance(desc, property) or type(desc).__name__ in (
                'cached_property', 'functools.cached_property'):
            fget = getattr(desc, 'fget', None) or getattr(desc, 'func', None)
            if isinstance(fget, types.FunctionType):
                found.append(('PROP', path + '.' + n, t.__name__,
                              getattr(fget, '__qualname__', '?')))
        try:
            v = getattr(obj, n)
        except Exception:
            continue
        if isinstance(v, (str, bytes, int, float, bool, type(None))):
            continue
        p = path + '.' + n
        if len(p) > 120:
            continue
        if id(v) in seen:
            continue
        depth[p] = d + 1
        queue.append((p, v))

for f in sorted(set(map(repr, found))):
    print(f)
