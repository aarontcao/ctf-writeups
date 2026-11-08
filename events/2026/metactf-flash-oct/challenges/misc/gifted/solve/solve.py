#!/usr/bin/env ctf-python
"""GIFted: each GIF frame is one tile of a QR code, not an overlay.
Laid out in a square grid in frame order, row major, the tiles rebuild the QR.
Reads the handout zip, not the gif on disk."""

import io
import math
import pathlib
import subprocess
import sys
import tempfile
import zipfile

from PIL import Image

_here = pathlib.Path(__file__).resolve()
for _p in _here.parents:
    if (_p / "lib" / "ctf.py").is_file():
        sys.path.insert(0, str(_p / "lib"))
        break

import ctf  # noqa: E402


def load_gif_bytes() -> bytes:
    """Pull gift.gif out of the pristine handout zip."""
    zpath = ctf.handout("gifted.zip")
    with zipfile.ZipFile(zpath) as z:
        name = next(n for n in z.namelist() if n.lower().endswith(".gif"))
        return z.read(name)


def reassemble(gif_bytes: bytes) -> Image.Image:
    """Tile the frames into the full QR."""
    im = Image.open(io.BytesIO(gif_bytes))
    frames = []
    for i in range(im.n_frames):
        im.seek(i)
        frames.append(im.convert("L").copy())
    n = len(frames)
    side = int(round(math.sqrt(n)))
    if side * side != n:
        raise SystemExit(f"frame count {n} is not a perfect square")
    w, h = frames[0].size
    big = Image.new("L", (w * side, h * side), 255)
    for i, f in enumerate(frames):
        r, c = divmod(i, side)
        big.paste(f, (c * w, r * h))
    return big


def decode_qr(img: Image.Image) -> str:
    """Decode with zbarimg after a 4x nearest-neighbor upscale."""
    big = img.resize((img.width * 4, img.height * 4), Image.NEAREST)
    with tempfile.NamedTemporaryFile(suffix=".png") as tf:
        big.save(tf.name)
        out = subprocess.run(
            ["zbarimg", "--quiet", "--raw", tf.name],
            capture_output=True,
            text=True,
            check=False,
        )
    return out.stdout.strip()


def solve() -> str:
    qr = reassemble(load_gif_bytes())
    return decode_qr(qr)


def main():
    text = solve()
    print(f"[*] QR payload: {text!r}")
    ctf.win(text)


if __name__ == "__main__":
    main()
