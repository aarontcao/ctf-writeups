#!/usr/bin/env ctf-python
"""Hatevibe: static decode of the maldoc, nothing is run.
The numbered doc variables in settings.xml hex-decode to an HTA. Its VBScript.Encode
blob decodes to a script that XORs a hex blob into the C2 beacon holding the flag."""

import io
import pathlib
import re
import sys
import zipfile

_here = pathlib.Path(__file__).resolve()
for _p in _here.parents:
    if (_p / "lib" / "ctf.py").is_file():
        sys.path.insert(0, str(_p / "lib"))
        break

import ctf  # noqa: E402

# MS Script Encoder decode tables, from Didier Stevens' decode-vbe.py.
DDECODE = {9: '\x57\x6E\x7B', 10: '\x4A\x4C\x41', 11: '\x0B\x0B\x0B', 12: '\x0C\x0C\x0C', 13: '\x4A\x4C\x41', 14: '\x0E\x0E\x0E', 15: '\x0F\x0F\x0F', 16: '\x10\x10\x10', 17: '\x11\x11\x11', 18: '\x12\x12\x12', 19: '\x13\x13\x13', 20: '\x14\x14\x14', 21: '\x15\x15\x15', 22: '\x16\x16\x16', 23: '\x17\x17\x17', 24: '\x18\x18\x18', 25: '\x19\x19\x19', 26: '\x1A\x1A\x1A', 27: '\x1B\x1B\x1B', 28: '\x1C\x1C\x1C', 29: '\x1D\x1D\x1D', 30: '\x1E\x1E\x1E', 31: '\x1F\x1F\x1F', 32: '\x2E\x2D\x32', 33: '\x47\x75\x30', 34: '\x7A\x52\x21', 35: '\x56\x60\x29', 36: '\x42\x71\x5B', 37: '\x6A\x5E\x38', 38: '\x2F\x49\x33', 39: '\x26\x5C\x3D', 40: '\x49\x62\x58', 41: '\x41\x7D\x3A', 42: '\x34\x29\x35', 43: '\x32\x36\x65', 44: '\x5B\x20\x39', 45: '\x76\x7C\x5C', 46: '\x72\x7A\x56', 47: '\x43\x7F\x73', 48: '\x38\x6B\x66', 49: '\x39\x63\x4E', 50: '\x70\x33\x45', 51: '\x45\x2B\x6B', 52: '\x68\x68\x62', 53: '\x71\x51\x59', 54: '\x4F\x66\x78', 55: '\x09\x76\x5E', 56: '\x62\x31\x7D', 57: '\x44\x64\x4A', 58: '\x23\x54\x6D', 59: '\x75\x43\x71', 60: '\x4A\x4C\x41', 61: '\x7E\x3A\x60', 62: '\x4A\x4C\x41', 63: '\x5E\x7E\x53', 64: '\x40\x4C\x40', 65: '\x77\x45\x42', 66: '\x4A\x2C\x27', 67: '\x61\x2A\x48', 68: '\x5D\x74\x72', 69: '\x22\x27\x75', 70: '\x4B\x37\x31', 71: '\x6F\x44\x37', 72: '\x4E\x79\x4D', 73: '\x3B\x59\x52', 74: '\x4C\x2F\x22', 75: '\x50\x6F\x54', 76: '\x67\x26\x6A', 77: '\x2A\x72\x47', 78: '\x7D\x6A\x64', 79: '\x74\x39\x2D', 80: '\x54\x7B\x20', 81: '\x2B\x3F\x7F', 82: '\x2D\x38\x2E', 83: '\x2C\x77\x4C', 84: '\x30\x67\x5D', 85: '\x6E\x53\x7E', 86: '\x6B\x47\x6C', 87: '\x66\x34\x6F', 88: '\x35\x78\x79', 89: '\x25\x5D\x74', 90: '\x21\x30\x43', 91: '\x64\x23\x26', 92: '\x4D\x5A\x76', 93: '\x52\x5B\x25', 94: '\x63\x6C\x24', 95: '\x3F\x48\x2B', 96: '\x7B\x55\x28', 97: '\x78\x70\x23', 98: '\x29\x69\x41', 99: '\x28\x2E\x34', 100: '\x73\x4C\x09', 101: '\x59\x21\x2A', 102: '\x33\x24\x44', 103: '\x7F\x4E\x3F', 104: '\x6D\x50\x77', 105: '\x55\x09\x3B', 106: '\x53\x56\x55', 107: '\x7C\x73\x69', 108: '\x3A\x35\x61', 109: '\x5F\x61\x63', 110: '\x65\x4B\x50', 111: '\x46\x58\x67', 112: '\x58\x3B\x51', 113: '\x31\x57\x49', 114: '\x69\x22\x4F', 115: '\x6C\x6D\x46', 116: '\x5A\x4D\x68', 117: '\x48\x25\x7C', 118: '\x27\x28\x36', 119: '\x5C\x46\x70', 120: '\x3D\x4A\x6E', 121: '\x24\x32\x7A', 122: '\x79\x41\x2F', 123: '\x37\x3D\x5F', 124: '\x60\x5F\x4B', 125: '\x51\x4F\x5A', 126: '\x20\x42\x2C', 127: '\x36\x65\x57'}
DCOMBINATION = [0, 1, 2, 0, 1, 2, 1, 2, 2, 1, 2, 1, 0, 2, 1, 2, 0, 2, 1, 2, 0, 0, 1, 2, 2, 1, 0, 2, 1, 2, 2, 1, 0, 0, 2, 1, 2, 1, 2, 0, 2, 0, 0, 1, 2, 0, 2, 1, 0, 2, 1, 2, 0, 0, 1, 2, 2, 0, 0, 1, 2, 0, 2, 1]


def vbe_decode(data: str) -> str:
    result = ""
    index = -1
    data = (data.replace('@&', chr(10)).replace('@#', chr(13))
                .replace('@*', '>').replace('@!', '<').replace('@$', '@'))
    for char in data:
        byte = ord(char)
        if byte < 128:
            index += 1
        if (byte == 9 or 31 < byte < 128) and byte not in (60, 62, 64):
            char = DDECODE[byte][DCOMBINATION[index % 64]]
        result += char
    return result


def read_doc_bytes() -> bytes:
    """Return the inner .doc, an OOXML zip, from the handout."""
    zpath = ctf.handout("hatevibe.zip")
    with zipfile.ZipFile(zpath) as z:
        name = next(n for n in z.namelist() if n.lower().endswith(".doc"))
        return z.read(name)


def solve() -> str:
    doc = read_doc_bytes()

    # The zip stores member names with backslash separators.
    with zipfile.ZipFile(io.BytesIO(doc)) as z:
        sname = next(n for n in z.namelist()
                     if n.replace("\\", "/").endswith("word/settings.xml"))
        settings = z.read(sname).decode("utf-8")

    pairs = re.findall(r'docVar w:name="(.*?)" w:val="(.*?)"', settings)
    # Numbered vars are the HTA's hex chunks in order.
    chunks = sorted((p for p in pairs if p[0][:1].isdigit()),
                    key=lambda p: int(p[0][:4]))
    hta = bytes.fromhex("".join(v for _, v in chunks)).decode("latin1")

    m = re.search(r"#@~\^......==(.+)......==\^#~@", hta, re.S)
    stage3 = vbe_decode(m.group(1))

    hexblob = re.search(r'temp\("([0-9A-Fa-f]+)"\)', stage3).group(1)
    key = re.search(r'Xor Asc\(Mid\("([^"]+)"', stage3).group(1).encode("latin1")
    blob = bytes.fromhex(hexblob)
    final = bytes(blob[j] ^ key[j % len(key)] for j in range(len(blob)))

    return final.decode("latin1")


def main():
    payload = solve()
    print(payload)
    return ctf.win(payload)


if __name__ == "__main__":
    main()
