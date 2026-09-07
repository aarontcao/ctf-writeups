"""
Scan every loaded module's namespace for implicit-call gadgets.
"""
import sys
import types

DUNDERS = ('__getitem__', '__getattr__', '__bool__', '__len__', '__iter__',
           '__contains__', '__index__', '__hash__', '__eq__', '__next__',
           '__call__', '__missing__')

hits = []
seen = set()


def note(s):
    hits.append(s)


def inspect(path, obj, d):
    if d > 3 or id(obj) in seen:
        return
    seen.add(id(obj))
    t = obj if isinstance(obj, type) else type(obj)
    # instances: implicit-call dunders on their type
    if not isinstance(obj, type):
        for dn in DUNDERS:
            f = getattr(type(obj), dn, None)
            if isinstance(f, types.FunctionType) and dn != '__call__':
                note('INST %-14s %s (type %s) -> %s' % (dn, path, type(obj).__name__, f.__qualname__))
    else:
        for dn in DUNDERS:
            f = obj.__dict__.get(dn)
            if isinstance(f, types.FunctionType):
                note('CLASS %-13s %s -> %s' % (dn, path, f.__qualname__))
            if isinstance(f, classmethod):
                note('CLASSCM %-11s %s -> %r' % (dn, path, f))
    if isinstance(obj, types.ModuleType):
        if '__getattr__' in obj.__dict__:
            note('MODGETATTR %s' % path)
        items = list(obj.__dict__.items())
    elif isinstance(obj, type):
        items = list(obj.__dict__.items())
    elif isinstance(obj, dict):
        items = [(str(k), v) for k, v in list(obj.items())]
    else:
        return
    for n, v in items:
        if isinstance(v, property) and isinstance(v.fget, types.FunctionType):
            note('PROP  %s.%s -> %s' % (path, n, v.fget.__qualname__))
        if type(v).__name__ == 'cached_property':
            note('CACHED %s.%s' % (path, n))
        if isinstance(v, (str, bytes, int, float, bool, type(None))):
            continue
        inspect(path + '.' + n, v, d + 1)


inspect('sys.modules', sys.modules, 0)
for h in sorted(set(hits)):
    print(h)
