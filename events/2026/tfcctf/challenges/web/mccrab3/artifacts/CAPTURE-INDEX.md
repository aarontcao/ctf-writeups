# mccrab3: capture index

These files hold raw request and response bytes, captured after the contest over a plain socket so a client library can't normalize the framing. mccrab3 is a Rust proxy (`proxoxy`, on container port 8888) in front of a Flask app on 127.0.0.1:8900, without a UI.

- I captured it on 2026-09-06 at 13:39Z.
- If every reply is `HTTP/1.1 404 Not Found` with the body `404 page not found`, your instance has expired and the cluster ingress is answering.

## How to read the results

A dropped connection means proxoxy matched a rule or failed to parse the request. A `500` means the request cleared the proxy and Flask errored without the header it wants, so `500` marks "passed the WAF".

All files are in `live-2026-09-06/`.

| file | request | result | what it establishes |
|---|---|---|---|
| `70-get-root.http` | `GET /` | 404 from Flask | The proxy passes ordinary traffic; Flask has no route at `/`. |
| `71-get-flag-blocked.http` | `GET /flag` | **dropped** | Rule (a): method GET on path `/flag`. A decoy, since the Flask route is POST-only anyway. |
| `72-post-flag-no-header.http` | `POST /flag`, no `brevski` | 500 | Clears the proxy, reaches gunicorn. Establishes the 500 marker. |
| `73-post-flag-brevski-george.http` | `POST /flag`, `brevski: george` | **dropped** | Rule (b). This one line is the entire challenge. |
| `74-post-flag-brevski-case.http` | `BrEvSkI: GeOrGe` | 500 | The rule does not fold case, so this clears the proxy. It is **not** a bypass: Flask's own check is also case-sensitive on the value, so the app still refuses. |
| `75-post-flag-brevski-wrong.http` | `brevski: notgeorge` | **dropped** | The rule is a **substring** match, not equality. Any value containing `george` dies. |
| `78-brevski-gorge-control.http` | `brevski: gorge` | 500 | **Control** for the row above. One letter off and it clears, so the drop is the substring rule firing and not a blanket ban on the `brevski` header. |
| `76-cl-te-both-dropped.http` | `Content-Length` and `Transfer-Encoding` together | **dropped** | proxoxy refuses the pairing outright, which closes the classic CL/TE desync. |
| `77-te-identity-dropped.http` | `Transfer-Encoding: identity` | **dropped** | proxoxy drops any TE whose final coding is not `chunked`, which closes the gunicorn `EOFReader` path that would otherwise have desynced. |

In row 74 only the value's case matters. proxoxy lowercases every header name before the rule runs, so `BrEvSkI: GeOrGe` clears on its value.

`00-INDEX.txt` lists the first response line of each exchange. `shot-01-landing-404.png` is a browser screenshot of Flask's 404 at `/`. The capture script isn't in the repo, but each `.http` file holds the exact request bytes.
