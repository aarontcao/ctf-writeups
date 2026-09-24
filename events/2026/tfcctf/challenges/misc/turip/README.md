# turip

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | misc |
| Difficulty | grandpa |
| Author | mcsky23 |
| Points at close | 170 |
| Solves | 90 |
| Status | solved |

> https://youtu.be/145Qd0aVTEk
>                                                             http://2.29.39.4:1337

Files: [`turip.zip`](handout/turip.zip), unpacked at [`chall/`](handout/chall) so you can read `app.py` without downloading it

<details>
<summary><b>Solution</b></summary>

## Solution

One TCP connection has to be two different byte streams at once, byte-exact for gunicorn
and needle-free for the packet capture watching the same wire, and the primitive that
splits them is TCP urgent data. Linux with `SO_OOBINLINE` off, which is every socket
gunicorn ever accepts, removes the urgent byte from the receiver's byte stream before the
application reads it, while gopacket reassembles from segment payloads and keeps every byte.
So `send(chunk, socket.MSG_OOB)` puts a byte on the wire that the server process provably
never sees, and three of those, one inside each forbidden string, are the whole exploit.

## Recon, in the order it ran

```bash
unzip -o handout/turip.zip -d handout/chall
ls handout/chall/                    # Dockerfile app.py entrypoint.sh
                                     # requirements.txt start_capture.sh build_docker.sh
wc -l handout/chall/app.py           # 466
grep -n 'NEEDLE\|CANONICAL\|BARRIER' handout/chall/app.py
grep -n 'tcpdump\|assembler' handout/chall/start_capture.sh
grep -n 'TULIP_COMMIT\|git fetch' handout/chall/Dockerfile
```

![top: handout listing; bottom: the two background processes](media/01-setup-handout-and-capture-pipeline.png)

`start_capture.sh` is where the challenge lives.

```bash
nohup tcpdump -Z root -i any -G 15 -w "${TRAFFIC_DIR}/capture-%Y%m%d-%H%M%S.pcap.tmp" \
    -z /usr/local/bin/finish-pcap port 1337 &
nohup /tulip/go-importer/assembler -skipchecksum -disable-converters \
    -dir "${TRAFFIC_DIR}" -timescale "${TIMESCALE}" &
```

That is [Tulip](https://github.com/OpenAttackDefenseTools/tulip), the attack-defense traffic
browser, rotating a pcap every fifteen seconds and feeding it to a gopacket assembler that
writes reconstructed flows into TimescaleDB. The Dockerfile pins Tulip to commit
`523e5179043a5b6ae1bbcc1990d774f23166319b` and asserts the hash after fetching it, so the
author wants you reading one exact revision of that code rather than whatever `main` happens
to say today.

## The two gates, read off app.py

`POST /get_flag1337` is a byte-equality check dressed up as a route. It demands that
`request.environ["RAW_URI"]` equal `/get_flag1337` exactly, that no `Transfer-Encoding` or
`Content-Encoding` header be present, that the mimetype be `application/json`, that
`Content-Length` be 50, and that the raw body equal the fifty bytes
`{"supersecretkey":"turip_ip_ip","ip":"1337.0.0.1"}`. On success it saves a UUID for your
team and echoes that UUID back as an `X-Traffic-Barrier` response header.

`GET /check` then runs one SQL query against Tulip's own tables, and that query is the real
specification of the challenge. It wants a flow whose server-direction items concatenate to
something containing `X-Traffic-Barrier: <your uuid>`, and whose client-direction items
concatenate to something containing none of the five needles `get_flag1337`, `turip_ip_ip`,
`1337.0.0.1`, `GET /get_flag1337`, and `POST /get_flag1337`.

![the two gates in app.py](media/02-recon-the-two-gates.png)

Sending the request honestly confirms the constraint: gunicorn answers 200 with the marker, the pcap rotates, and `/check` comes back 400 with `forbidden request data was visible in your captured flow`. The challenge reduces to finding where the application and the capture disagree about what was on the wire.

![the honest request is accepted, then caught](media/03-recon-honest-request-is-caught.png)

## Reading the assembler for a blind spot

The pinned revision is small enough to read end to end, and four properties of it decide
which tricks remain available.

```bash
git clone https://github.com/OpenAttackDefenseTools/tulip scratch/tulip
git -C scratch/tulip checkout 523e5179043a5b6ae1bbcc1990d774f23166319b
sed -n '1,120p' scratch/tulip/services/go-importer/cmd/assembler/tcp.go
grep -n 'ip4defrag\|nonstrict\|TCPDirClientToServer' \
    scratch/tulip/services/go-importer/cmd/assembler/main.go
grep -n 'direction' scratch/tulip/services/go-importer/cmd/assembler/http.go
```

Direction is `gopacket.TCPDirClientToServer`, fixed by the first packet of the stream, so
there is no way to get your own request filed as server traffic. The reassembly FSM runs
strict, `nonstrict` being false, so a stream missing a visible SYN handshake has every
packet rejected and yields an empty flow. The assembler invokes `ip4defrag` before handing
anything to the TCP layer, and a first fragment on its own returns nil and is skipped
entirely. `ParseHttpFlow` rewrites only server items, and only to un-gzip or un-brotli a
response body, so no content-encoding trick reaches the client half.

Chunked and compressed request bodies are rejected by `app.py` anyway, and Tulip stores client bytes raw, so any encoding that hides a needle from Tulip hides it from gunicorn too. The answer is below HTTP: a disagreement about the bytes themselves.

## Dead end: IP fragmentation, correct and out of reach

If the HTTP request leaves as IP fragments, the BPF filter `port 1337` matches only the
first fragment, because a non-first fragment lacks a TCP header and therefore any port
number for the filter to read. Tulip's own `ip4defrag` then returns nil on that lone first
fragment and skips it. The receiving kernel meanwhile reassembles the datagram normally and
hands gunicorn a complete request. Keep the handshake and the response unfragmented so the
FSM stays happy, and the marker still lands in the server direction while the client stream
ends up with zero flow items, which makes `forbidden_seen` false by vacuity.

I spent a while checking whether Docker's bridge NAT would defeat this, and it does not.
Host conntrack defragments in PREROUTING, but `ip_do_fragment` refragments the reassembled
skb using `IPCB(skb)->frag_max_size`, which is the original fragment size rather than the
veth MTU, so small fragments go in and small fragments come out onto the veth.
`solve/rawtcp.py` is the userland TCP stack written for this route, built on scapy, with a
`send_data(payload, fragsize=...)` and a `send_decoy_then_real` helper for the bad-checksum
variant, and `solve/test_health.py` fires a fragmented `GET /health` at the live host
because `/health` is unauthenticated and free of rate limits.

The route died on capability, not on correctness. Raw sockets need `CAP_NET_RAW`, the
userland stack needs an iptables rule dropping the kernel's own RST for the port it is
spoofing, and the egress NAT in front of me might well drop IPv4 fragments outright. With a
ten-second per-team rate limit on every authenticated endpoint, spending attempts on a route
with three independent ways to fail was the wrong order of operations.

The `-skipchecksum` flag hints at a second route I never opened. Tulip ingests segments
whose TCP checksum is wrong and Linux drops them, so a bad-checksum decoy at the same
sequence number should win the overlap inside gopacket while the real segment reaches the
application. It is untested, and I am recording it as untested rather than as working.

## The urgent byte

The question that led to TCP urgent data is what other mechanism, short of raw sockets, lets
a sender put a byte into a segment payload that the receiving application will not read.
The answer is `MSG_OOB`, which is available to any unprivileged socket.

TCP urgent data is specified in [RFC 6093](https://www.rfc-editor.org/rfc/rfc6093), which is
mostly a long argument that nobody should use it. On Linux, when a segment arrives with the
URG flag set and the receiving socket has `SO_OOBINLINE` disabled, the kernel lifts the byte
at the urgent pointer out of the receive queue and stashes it where only `recv(MSG_OOB)` can
reach it. A process that never asks for out-of-band data, which is every process gunicorn
runs, reads a byte stream with that byte deleted. gopacket does nothing of the kind, since
it reassembles from segment payloads and lacks any notion of an urgent pointer at all.

`solve/test_oob_local.py` proves the whole thing over loopback, using only local sockets:

```python
oob(b"GET /hZ"); oob(b"eaX"); oob(b"ltY"); plain(b"h HTTP/1.1\r\n\r\n")
# wire     : b'GET /hZeaXltYh HTTP/1.1\r\n\r\n'
# app saw  : b'GET /health HTTP/1.1\r\n\r\n'
```

Three urgent bytes, three deletions, and a loopback socket that reads a different request
from the one that went out. `solve/test_oob_remote.py` repeats it against the live host on
the unauthenticated `/health` route, which answers the one question the local test cannot,
namely whether the urgent pointer survives the egress NAT and the container's bridge. It
does, and a 200 on `/health` from a wire that spelled `/hZeaXltYh` is the confirmation.

![a TCP urgent byte is on the wire but never in the app's read](media/04-insight-tcp-urgent-byte-vanishes.png)

## The finished request

`solve/solve.py` sends the canonical request as five chunks, three of them urgent, with each
urgent chunk ending in one junk byte placed inside a needle:

```python
parts = [
    (b"POST /get_flZ", True),                 # breaks  get_flag1337
    (headers, False),
    (b'{"supersecretkey":"turip_X', True),    # breaks  turip_ip_ip
    (b'ip_ip","ip":"1337.Y', True),           # breaks  1337.0.0.1
    (b'0.0.1"}', False),
]
```

The script derives both byte streams from that table and asserts on them before it opens a
socket, so a mistake in the split gets caught offline instead of against a rate-limited
endpoint. On the wire: `POST /get_flZag1337`, `turip_Xip_ip`, and `1337.Y0.0.1`, which
match zero needles. The concatenation with each urgent last byte removed is the canonical
request byte for byte.

![the request cut into five chunks](media/05-insight-request-split-into-urgent-chunks.png)

The 0.6 second gap between sends is there because the kernel keeps a single `urg_seq` per
socket, and a second urgent byte arriving before the reader has consumed the first
overwrites it, at which point one of the junk bytes lands in gunicorn's stream and the
body-equality check fails; the local test found the floor near 0.4 seconds and the live run
used 0.6 for margin.

Against the contest instance the flag request returned 200 with `X-Traffic-Barrier`, and
`/check` returned the flag on the first poll, 33 seconds later, which is one pcap rotation
plus ingest. Side by side, Tulip's stored client stream for the honest run and for the
exploit run are two different HTTP requests, while gunicorn read the same fifty bytes both
times.

![Tulip UI showing the honest request with all three needles present](media/06-insight-tulip-sees-the-honest-request.png)

![Tulip's view of the exploit: a different request entirely](media/07-insight-tulip-sees-a-different-request.png)

## Reproduce

```bash
python3 solve/test_oob_local.py         # the primitive, no network
python3 solve/test_oob_remote.py 0.4    # the primitive, against the live /health
python3 solve/solve.py --probe          # send the flag request only
python3 solve/solve.py                  # send it, then poll /check
```

![local rebuild showing all needles false on wire, true in app, then flag returned](media/08-exploit-local-rebuild-end-to-end.png)

![contest run showing flag capture and submission](media/09-flag-recorded-contest-flag.png)

Flag: `TFCCTF{this_was_discovered_in_the_good_old_days_when_people_still_played_ctf}`
</details>
