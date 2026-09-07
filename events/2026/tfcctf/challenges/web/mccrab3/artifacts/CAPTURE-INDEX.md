# mccrab3: capture index

Post-contest evidence capture. mccrab3 finished at 5 solves. We fired roughly
28,700 probes at it and did not land the bypass.

mccrab3 has **no rendered UI**. It is a Rust proxy (`proxoxy`, listening on
container port 8888) in front of a Flask app on 127.0.0.1:8900, and the only
interesting surface is the proxy's rule engine. So this capture is raw request
and response **bytes**, sent over a plain socket rather than through a client
library, because the whole challenge lives in framing that a library would
normalise away. One screenshot exists and it is deliberately boring.

- Instance: `mccrab3-98c36152b68129b7`, nodeport `special.thefewchosen.com:30494` mapping to container 8888. Started 13:38Z on 2026-09-06.
- A first attempt at 13:37Z hit the **previous** deployment's nodeport, 30570, after that deployment had already expired. Every reply was `HTTP/1.1 404 Not Found` with `Content-Type: text/plain` and the body `404 page not found`, which is the Go `net/http` default page from the cluster ingress, not from proxoxy. Those files were discarded. If you see that exact 404 shape, you are talking to the ingress and your container is gone.
- The reproducer is `../scratch/capture.py <host> <port>`.

## How to read the results

A **dropped connection with no response at all** means proxoxy matched a rule
and killed the request. A **500 from gunicorn** means the request cleared the
proxy and reached Flask, which errors when it does not get the header it wants.
So `500` is the marker for "passed the WAF", not a failure.

All files are in `live-2026-09-06/`, taken 2026-09-06 at 13:39Z.

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

`00-INDEX.txt` records the target, the capture timestamp and the first response
line of each exchange.

| file | what it shows |
|---|---|
| `shot-01-landing-404.png` | `http://special.thefewchosen.com:30494/` in a browser: Flask's 404. Included only so the writeup can state that there is no UI here and show it rather than assert it. |

## What is not here

The bypass. The last unread code path at the time we stopped was
`parse_request_cookies` at `0x122c10`, the only other place proxoxy builds a
separate structure out of a header, and it is the same shape that produced the
trailer bug we did find. The handout `mccrab3.zip` is on disk, so that path
remains readable offline for as long as anyone cares to read it.
