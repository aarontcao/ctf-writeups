# CTF writeups

Solutions and writeups from capture-the-flag events.

## Running a solve script

`ctf-python` is Python with pwntools and `lib/` on `PYTHONPATH`. `ctf-sandbox` is our local Docker wrapper for running organizer binaries, and it isn't published. The recorded target is the host and port in the challenge's `meta.json`.

    CTF_LOCAL=1 ctf-python solve.py                  against the local handout
    ctf-python solve.py                              against the recorded target
    CTF_TARGET='nc host 1337' ctf-python solve.py    against an override

The per-challenge `scratch/` helpers aren't published, so a Reproduce step that names one won't run from a clone.

## License

AGPL-3.0-or-later. See [LICENSE](LICENSE). Files under any `handout/` directory belong to the challenge authors and aren't covered by this license.
