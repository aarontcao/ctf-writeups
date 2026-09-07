#!/usr/bin/env ctf-python
"""
Solve template: rev.

Recon ladder:
    file handout/*                     format, arch, stripped or not
    strings -n 8 handout/*             often the whole challenge
    checksec handout/chall
    ghidra-decompile handout/chall     writes artifacts/chall.c

Never run an unknown binary on the host, use `ctf-sandbox ./handout/chall`.
angr is here for when the check is just a pure function of the input.
"""

import pathlib
import sys

# Walk up for lib/ctf.py. Counting parent directories breaks when a level is added.
_here = pathlib.Path(__file__).resolve()
for _p in _here.parents:
    if (_p / "lib" / "ctf.py").is_file():
        sys.path.insert(0, str(_p / "lib"))
        break

import ctf  # noqa: E402

BINARY = ctf.handout("chall")


def with_angr(find, avoid=()):
    """
    Symbolically execute to `find`, avoiding `avoid`. Returns the stdin that
    reaches the target address. Cheap for a single check function, but doesn't work
    once the binary loops over network input. Read the decompilation first.
    """
    import angr
    import claripy

    proj = angr.Project(str(BINARY), auto_load_libs=False)
    flag_len = 40
    chars = [claripy.BVS(f"c{i}", 8) for i in range(flag_len)]
    flag = claripy.Concat(*chars, claripy.BVV(b"\n"))

    st = proj.factory.full_init_state(stdin=flag, add_options=angr.options.unicorn)
    for c in chars:
        st.solver.add(claripy.Or(c == 0x7D, claripy.And(c >= 0x20, c <= 0x7E)))

    sm = proj.factory.simulation_manager(st)
    sm.explore(find=find, avoid=list(avoid))
    if not sm.found:
        return None
    return sm.found[0].posix.dumps(0)


def with_z3(constraints_builder):
    """Solve a constraint system lifted by hand from the decompilation."""
    import z3

    s = z3.Solver()
    flag = [z3.BitVec(f"f{i}", 8) for i in range(40)]
    constraints_builder(s, flag)
    if s.check() != z3.sat:
        return None
    m = s.model()
    return bytes(m[c].as_long() for c in flag)


def main():
    out = with_angr(find=0x0)
    if out:
        ctf.win(out)
    else:
        raise SystemExit("no path found, read artifacts/chall.c instead")


if __name__ == "__main__":
    main()
