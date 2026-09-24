# Discord Shenanigans v6

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | misc |
| Difficulty | baby |
| Author | hofill |
| Points at close | 50 |
| Solves | 265 |
| Status | solved |

> You already know. We don't want this challenge to be guessy. Wrap the hidden word in TFCCTF{}. It's in #announcements.

<details>
<summary><b>Solution</b></summary>

## Solution

The hidden word is an acrostic. Taking the first letter of each sentence of the previous
day's `#announcements` post gives Come, Assemble, Stay, The, Let, Everyone, which spells
CASTLE, and everything in the message is technically in the open.

![top: the title and a line naming the two panels; left: the #announcements post with the first letter of each sentence boxed in red; right: the six sentence initials, the word CASTLE, the flag, and a note that the message is plain ASCII](media/05-insight-acrostic.png)

## Recon: the Unicode sweep comes back empty

The prompt names one message in one channel, so the whole of the recon is a copy out of
Discord, preserving every codepoint, followed by a decode. The target is Noria's post in
the #announcements channel.

![top: the #announcements channel header; middle: Noria's post, with the @everyone opening line and the six sentences below it; bottom: the event link](media/03-recon-announcement.png)

```bash
python3 -c "
t = open('scratch/announcement.txt', encoding='utf-8').read()
print(sorted({hex(ord(c)) for c in t if ord(c) > 0x7f}))"
```

That prints an empty list. So every channel a text-stego decoder would inspect is empty before
the decoder runs. Running one anyway confirms it across zero-width
characters in `U+200B` through `U+200D` and `U+FEFF`, variation selectors in `U+FE00` through `U+FE0F` and
`U+E0100` through `U+E01EF`, tag characters in `U+E0000` through `U+E007F`, bidirectional
overrides in `U+202A` through `U+202E` and `U+2066` through `U+2069`, Cyrillic and Greek
homoglyphs, and combining marks. The message is plain ASCII and free of any encoding.

The acrostic check lives one function along in the same decoder.

```bash
python3 -c "
import re
t = open('scratch/announcement.txt', encoding='utf-8').read()
print(''.join(s.strip()[0] for s in re.split(r'(?<=[.!?])\s+', t) if s.strip()))"
# CASTLE
```

Run the acrostic check before the Unicode sweep: it costs one line and answers immediately.

Flag: `TFCCTF{CASTLE}`
</details>
