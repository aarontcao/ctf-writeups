#!/usr/bin/env ctf-python
"""PasswordlessChecks (rev), MetaCTF October 2026 Flash CTF.
The game saves a 16-character name typed on an Xbox controller, and that name is the flag body.
This replays the presses from capture.pcapng on the VX Window_NameInput grid."""

# Run: CTF_LOCAL=1 ctf-python solve/solve.py

import pathlib
import re
import subprocess
import sys
import tempfile
import zipfile

_here = pathlib.Path(__file__).resolve()
for _p in _here.parents:
    if (_p / "lib" / "ctf.py").is_file():
        sys.path.insert(0, str(_p / "lib"))
        break
import ctf  # noqa: E402

# Window_NameInput::ENGLISH from Data/Scripts.rvdata: 10 columns, 9 rows, 89 is OK.
ENGLISH = [
    "A", "B", "C", "D", "E", "a", "b", "c", "d", "e",
    "F", "G", "H", "I", "J", "f", "g", "h", "i", "j",
    "K", "L", "M", "N", "O", "k", "l", "m", "n", "o",
    "P", "Q", "R", "S", "T", "p", "q", "r", "s", "t",
    "U", "V", "W", "X", "Y", "u", "v", "w", "x", "y",
    "Z", " ", " ", " ", " ", "z", " ", " ", " ", " ",
    " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
    "1", "2", "3", "4", "5", " ", " ", " ", " ", " ",
    "6", "7", "8", "9", "0", " ", " ", " ", " ", "OK",
]

# Byte 5 of a GIP input report is the D-pad bitmask.
UP, DOWN, LEFT, RIGHT = 0x01, 0x02, 0x04, 0x08
SELECT = 0x40  # byte 4: Xbox X, which picks a letter


def cursor_move(i: int, bit: int) -> int:
    """Window_NameInput cursor moves, with wraparound."""
    if bit == UP:
        return i - 10 if i >= 10 else i + 80
    if bit == DOWN:
        return i + 10 if i < 80 else i - 80
    if bit == LEFT:
        return i - 1 if i % 10 > 0 else i + 9
    if bit == RIGHT:
        return i + 1 if i % 10 < 9 else i - 9
    return i


def pcap_path() -> pathlib.Path:
    """Extract capture.pcapng from the handout zip into a temp dir."""
    zpath = ctf.handout("passwordless-checks.zip")
    out = pathlib.Path(tempfile.mkdtemp(prefix="pwless_"))
    with zipfile.ZipFile(zpath) as z:
        member = next(n for n in z.namelist() if n.endswith("capture.pcapng"))
        z.extract(member, out)
        return out / member


def input_reports(pcap: pathlib.Path) -> list[bytes]:
    """Device->host GIP input reports (message type 0x20)."""
    res = subprocess.run(
        ["tshark", "-r", str(pcap),
         "-Y", 'usb.capdata && usb.src=="2.4.2"',
         "-T", "fields", "-e", "usb.capdata"],
        check=True, capture_output=True, text=True,
    )
    reports = []
    for line in res.stdout.splitlines():
        line = line.strip().replace(":", "")
        if re.fullmatch(r"[0-9a-fA-F]+", line) and line.lower().startswith("2000"):
            reports.append(bytes.fromhex(line))
    return reports


def press_events(reports: list[bytes]) -> list[int]:
    """One event per fresh press. Byte 4 holds face buttons, byte 5 the D-pad."""
    events, prev = [], (0, 0)
    for r in reports:
        cur = (r[4], r[5])
        if cur != (0, 0) and cur != prev:
            if r[4] == SELECT:
                events.append(SELECT)
            elif r[5] in (UP, DOWN, LEFT, RIGHT):
                events.append(r[5])
            # 0x10 (Xbox A) only frames the session, so it's skipped.
        prev = cur
    return events


def decode(events: list[int]) -> str:
    """Replay the events from index 0, since actor 1 starts with an empty name."""
    idx, name = 0, []
    for ev in events:
        if ev == SELECT:
            ch = ENGLISH[idx]
            if ch != "OK":
                name.append(ch)
        else:
            idx = cursor_move(idx, ev)
    return "".join(name)


def main() -> None:
    pcap = pcap_path()
    reports = input_reports(pcap)
    events = press_events(reports)
    body = decode(events)
    print(f"[*] input reports : {len(reports)}")
    print(f"[*] press events  : {len(events)}")
    print(f"[*] decoded name  : {body!r}  ({len(body)} chars)")
    flag = f"MetaCTF{{{body}}}"
    print(f"[*] candidate flag: {flag}")
    ctf.win(flag)


if __name__ == "__main__":
    main()
