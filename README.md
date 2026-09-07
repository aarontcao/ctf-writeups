# CTF writeups

My solutions and writeups from capture-the-flag events. I lost access to my older GitHub account, so I'll try to backfill my writeups for past events (pre-2026) as I dig them up.

## Reproducing a solution (Python)

You can run `solve.py` against the local handout, the recorded target, or an override:

    CTF_LOCAL=1 ctf-python solve.py                  against the local handout
    ctf-python solve.py                              against the recorded target
    CTF_TARGET='nc host 1337' ctf-python solve.py    against an override

Usually challenge infrastructure is torn down after an event, so the remote mode probably won't reach anything. Sometimes you can stand a challenge up locally though. 

## Licence

AGPL-3.0-or-later. See [LICENSE](LICENSE). Challenge handouts under any `handout/` directory are the work of the challenge authors and are unmodified.
