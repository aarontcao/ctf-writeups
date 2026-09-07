"""
Targeted scan: find implicit-call gadgets reachable from sys, restricted to
lowercase+underscore attribute names, no 'ass'/'typ'/'als' substrings.
"""
import sys
import types
import re

NAME = re.compile(r'^[a-z_][a-z_]*$')
BAD = ('ass', 'typ', 'als')
DUNDERS = ('__getitem__', '__getattr__', '__bool__', '__len__', '__iter__',
           '__contains__', '__index__', '__hash__', '__eq__', '__next__',
           '__class_getitem__')


def ok(n):
    return bool(NAME.match(n)) and not any(b in n for b in BAD)


def pylevel(f):
    return isinstance(f, (types.FunctionType, types.MethodType,
                          types.MethodDescriptorType)) and isinstance(
        f, types.FunctionType)


hits = []
seen = set()


def inspect(path, obj, d):
    if d > 3:
        return
    if id(obj) in seen:
        return
    seen.add(id(obj))
    t = type(obj)
    for dn in DUNDERS:
        f = getattr(t, dn, None)
        if isinstance(f, types.FunctionType):
            hits.append(('%-10s %s  (type=%s) -> %s' % (
                dn, path, t.__name__, f.__qualname__)))
    if isinstance(obj, types.ModuleType) and '__getattr__' in obj.__dict__:
        hits.append('MODGETATTR %s -> %r' % (path, obj.__dict__['__getattr__']))
    try:
        names = [n for n in dir(obj) if ok(n)]
    except Exception:
        return
    for n in names:
        try:
            desc = getattr(t, n, None)
        except Exception:
            desc = None
        if isinstance(desc, property) and isinstance(desc.fget, types.FunctionType):
            hits.append('PROPERTY   %s.%s -> %s' % (path, n, desc.fget.__qualname__))
        if type(desc).__name__ == 'cached_property':
            hits.append('CACHEDPROP %s.%s' % (path, n))
        try:
            v = getattr(obj, n)
        except Exception:
            continue
        if isinstance(v, (str, bytes, int, float, bool, type(None), tuple, frozenset)):
            continue
        inspect(path + '.' + n, v, d + 1)


inspect('sys', sys, 0)
for h in sorted(set(hits)):
    print(h)
