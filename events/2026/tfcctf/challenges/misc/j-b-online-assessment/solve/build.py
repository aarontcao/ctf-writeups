"""
Rebuild job-oa.pka with the answer network copied into the user slot.

A .pka holds three <PACKETTRACER5> blocks: [0] the network the candidate works
on, [1] the initial network, [2] the answer network. Copying [2] over [0] makes
the submitted network identical to the answer.
"""

import re
import sys
_CH = __import__("os").path.dirname(__import__("os").path.dirname(__import__("os").path.abspath(__file__)))

sys.path.insert(0, f"{_CH}/solve")
import pka

BASE = f"{_CH}"


def blocks(s):
    starts = [m.start() for m in re.finditer(r"\n  <PACKETTRACER5>", s)]
    ends = [m.end() for m in re.finditer(r"\n  </PACKETTRACER5>", s)]
    return list(zip(starts, ends))


def main():
    keep_banks = "--keep-banks" in sys.argv
    out = sys.argv[1]
    s = open(f"{BASE}/scratch/job-oa.xml", encoding="utf-8").read()
    bs = blocks(s)
    a0, b0 = bs[0]
    a2, b2 = bs[2]
    answer = s[a2:b2]
    if keep_banks:
        cur = s[a0:b0]
        i = cur.index("<PIXMAPBANK>")
        j = cur.index("</MOVIEBANK>") + len("</MOVIEBANK>")
        banks = cur[i:j]
        k = answer.index("</VERSION>") + len("</VERSION>")
        answer = answer[:k] + "\n      " + banks + answer[k:]
    new = s[:a0] + answer + s[b0:]
    open(f"{BASE}/scratch/{out}.xml", "w", encoding="utf-8").write(new)
    blob = pka.encrypt_pka(new.encode("utf-8"))
    open(f"{BASE}/scratch/{out}.pka", "wb").write(blob)
    print(f"{out}: xml {len(new)} -> pka {len(blob)} ({len(blob)/1048576:.2f} MiB)")


main()
