# J*B Online Assessment

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | misc |
| Difficulty | baby |
| Author | cr0 |
| Points at close | 93 |
| Solves | 142 |
| Status | solved |

> Can you get a j*b in 2026?

Files: [`job-oa.pka`](handout/job-oa.pka)

<details>
<summary><b>Solution</b></summary>

## Solution

A Cisco Packet Tracer activity file holds three `<PACKETTRACER5>` blocks rather than one.
The third of them is the fully configured answer network that the grader compares your work
against. The file you are asked to complete already contains the completed version of
itself, so once the encryption is off, the solve is a string slice that pastes block 2 over
block 0, followed by a re-encrypt of the result.

Decrypting the file is the only real work. That part is a known algorithm with a public
reference implementation. Everything after it is bookkeeping.

## Recon, in the order it ran

```bash
file handout/job-oa.pka          # data
wc -c handout/job-oa.pka         # 3002321
xxd handout/job-oa.pka | head    # no magic, no header, high entropy throughout
```

The challenge is dynamic, so the first step is to start an instance. The convenience wrapper
in the toolkit pointed at the wrong host. The endpoint that starts a container lives on the
challenge manager rather than on the public API.

```bash
python3 solve/instapi.py POST /isolated '{"name":"j-b-online-assessment"}'
python3 solve/instapi.py GET  /isolated
```

`GET /isolated` returns a name, an expiry, and a connection string for each running instance.
The cap is three per team, so a POST during a busy stretch answers 409 and you wait. With one
running, the app at `https://<deployment>.challs.ctf.thefewchosen.com` turns out to be a Cisco
Packet Tracer assessment page. It serves `/downloads/job-oa.pka` and accepts the completed
file back through `POST /api/submit`, with the flag gated on 100 percent completion.

The screenshot below renders the archived HTML of that page, so it appears unstyled.

![The assessment page rendered from the archived HTML: top, the candidate banner and the instruction that only 100 percent completion counts; middle, the .pka download link; bottom, the upload form for the finished file.](media/01-setup-landing.png)

Submitting the untouched handout gives a progress meter before any reverse engineering:

```json
{"ok": false, "message": "Relay incomplete: 18/122 signed configuration markers recovered."}
```

The grader counts 122 configuration markers and the handout satisfies 18. So the target is
configuration text, and you have a score to watch.

## Decrypting the .pka

`.pka` is Packet Tracer's own container.
[pka2xml](https://github.com/mircodz/pka2xml) reverse engineered the format years ago and
documents it. The chain, read from the file on disk inward, is a byte-level obfuscation pass,
then Twofish in EAX mode, then a second obfuscation pass. Last comes a four-byte big-endian
length header followed by zlib. A wrong step anywhere in the middle produces noise rather than
a diagnosable error.

`solve/pka.py` reimplements both directions in pure Python, because the reference tool is C++
and building it was more work than transcribing 140 lines. The two obfuscation passes are
small enough to state outright:

```python
def _stage1(data):                      # reverse and XOR with a length-dependent counter
    n = len(data)
    return bytes(data[n - 1 - i] ^ ((n - i * n) & 0xFF) for i in range(n))

def _stage3(data):                      # XOR each byte with (len - index), an involution
    n = len(data)
    return bytes(b ^ ((n - i) & 0xFF) for i, b in enumerate(data))
```

The Twofish key is sixteen bytes of `137` and the IV is sixteen bytes of `16`. Both constants
are baked into Packet Tracer itself. EAX needs a CMAC over the cipher, which is another forty
lines. The tag is checked and warned about rather than enforced, since a rebuilt file
verifies fine and a handout with a stale tag should still decrypt.

The `twofish` package on PyPI sets one Python-side trap. It still does `import imp` at module
load, and `imp` was removed from the standard library. So the import fails on any modern
interpreter. `pka.py` installs a three-line shim module under that name before importing. The
shim is enough because only `find_module` is ever called.

```bash
python3 solve/pka.py -d handout/job-oa.pka scratch/job-oa.xml
# -d 3002321 -> 73855166 bytes
```

Three megabytes of ciphertext become 73.8 megabytes of XML. The XML declares itself
`PACKETTRACER5_ACTIVITY` version `8.2.1.0118`.

![A terminal session: top, ls, file, and xxd show the handout as opaque data; middle, solve/pka.py decrypts it to XML; bottom, the head of the XML with the PACKETTRACER5_ACTIVITY root and its version.](media/02-recon-decrypt-pka.png)

## Finding the answer key

```bash
grep -c '<PACKETTRACER5>' scratch/job-oa.xml        # 3
```

The XML has three blocks, plus a 45 megabyte `COMPARISONS` tree that holds the grading rubric.
Counting devices and configuration lines per block separates them at once. Block 2 has 55
devices and 6,239 configuration lines, where the other two have 51 and 5,187.

![A block survey of the decrypted XML: top, the XML size and the list of top-level elements; middle, a table of the three blocks with block 2 highlighted; bottom, the config comparisons between blocks and a note on which block is the answer.](media/03-recon-three-networks.png)

Router `Research-Core` makes the difference concrete. It has 123 configuration lines in the
candidate block and 249 in the answer block. The extra lines include every DHCP pool the
activity asks you to create. In the diff below, a `+` in the gutter marks a line that the
candidate config lacks.

![A side-by-side config diff for router Research-Core: left, the candidate block 0; right, the answer block 2, with highlighted plus rows for the DHCP excluded addresses and the four DHCP pools; bottom, a note that the graded work ships inside the handout.](media/04-insight-answer-inside.png)

Blocks 0 and 1 are byte-identical, so the file alone cannot tell you which of the two the
candidate is supposed to edit. Overwriting block 0, submitting, and reading the score is
cheaper than resolving that from Packet Tracer's source.

## The swap

`solve/build.py` locates the three blocks by regex on `\n  <PACKETTRACER5>` and
`\n  </PACKETTRACER5>`, slices the answer block out, and splices it over the candidate block.

```python
bs = blocks(s)
a0, b0 = bs[0]
a2, b2 = bs[2]
new = s[:a0] + s[a2:b2] + s[b0:]
```

The string slicing is deliberate. An XML parse of a 73 megabyte document is slow. Any
reserialization also risks perturbing whitespace or attribute order, and the grader may care
about either.

Two controls ran before the upload. The encryptor round-trips the untouched XML byte for byte,
and uploading that round-tripped file still scores 18 out of 122. That result proves that
re-encryption by itself leaves the score unchanged, and that any score change afterward comes
from the swap. The rebuilt file also decrypts back to XML with block 0 replaced and blocks 1
and 2 untouched. `cmp` matches it against the bytes actually uploaded.

![A local rerun of the swap after the event: top, the lines of build.py that paste block 2 over block 0 and re-encrypt; middle, the build output with the round-trip controls; bottom, the block checks on the rebuilt file and a cmp showing it equals the uploaded solution.pka.](media/05-exploit-swap-and-verify.png)

```bash
python3 solve/build.py answerswap
curl -s -F 'file=@scratch/answerswap.pka' \
     "https://<deployment>.challs.ctf.thefewchosen.com/api/submit"
```

The grader returned 122 out of 122 and the flag.

## What was not needed

`build.py` has a `--keep-banks` mode that copies the candidate block's `PIXMAPBANK` through
`MOVIEBANK` section into the answer block. It was built on the theory that the grader might key on
activity assets rather than on device configuration. The mode went unused, because the plain
swap scored 122 out of 122 on the first attempt.

Every step here runs outside Packet Tracer itself.

## Reproduce

```bash
python3 solve/pka.py -d handout/job-oa.pka scratch/job-oa.xml    # 3 MB -> 73.8 MB
python3 solve/build.py answerswap                                # swap and re-encrypt
python3 solve/pka.py -e scratch/answerswap.xml scratch/check.pka # round-trip control
```

`solve/instapi.py` is the challenge-manager client used to start and list instances.
`artifacts/solution.pka` is the file that scored, preserved alongside the archived page and
its `app.js`.

The last screenshot shows the lines written at the time, plus the `app.js` path proving the
flag came from the server response.

![The solve notes and archived files, read back after the event: top, the 18/122 attempt line; middle, the 122/122 verifier line, the submit line, and the app.js lines that render body.flag; bottom, the recorded flag above the meta.json summary.](media/06-flag.png)

Flag: `TFCCTF{cheating_is_the_only_way_to_get_a_job_in_2026}`
</details>
