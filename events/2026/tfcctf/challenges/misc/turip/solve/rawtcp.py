#!/usr/bin/env python3
"""
Minimal userland TCP client built on scapy raw sockets.

Purpose: send an HTTP request whose data-bearing IP datagram is split into
IP fragments, so a tcpdump 'port 1337' BPF filter on the far side only ever
matches the first fragment and the reassembler upstream of it sees nothing.
"""
import random
import sys
import threading
import time

from scapy.all import IP, TCP, Raw, AsyncSniffer, conf, fragment, send

conf.verb = 0


class RawTCP:
    def __init__(self, dst, dport, sport=None, iface="ens4", log=print):
        self.dst = dst
        self.dport = dport
        self.sport = sport or random.randint(20000, 60000)
        self.iface = iface
        self.log = log
        self.seq = random.randint(1, 2 ** 31 - 1)
        self.ack = 0
        self.rxbuf = b""
        self.rx_next = None
        self.pending = {}
        self.got_fin = False
        self.got_rst = False
        self.syn_ack = threading.Event()
        self.lock = threading.Lock()
        self.sniffer = None

    # ---------- plumbing ----------
    def _base(self, flags, seq=None, ack=None):
        return IP(dst=self.dst) / TCP(
            sport=self.sport,
            dport=self.dport,
            flags=flags,
            seq=self.seq if seq is None else seq,
            ack=self.ack if ack is None else ack,
            window=65535,
        )

    def _on(self, pkt):
        if TCP not in pkt:
            return
        t = pkt[TCP]
        with self.lock:
            if t.flags & 0x04:  # RST
                self.got_rst = True
                return
            if (t.flags & 0x02) and (t.flags & 0x10):  # SYN-ACK
                self.ack = t.seq + 1
                self.rx_next = t.seq + 1
                self.syn_ack.set()
                return
            payload = bytes(t.payload) if t.payload else b""
            if payload:
                if self.rx_next is not None:
                    if t.seq == self.rx_next:
                        self.rxbuf += payload
                        self.rx_next += len(payload)
                        # drain anything buffered out of order
                        while self.rx_next in self.pending:
                            d = self.pending.pop(self.rx_next)
                            self.rxbuf += d
                            self.rx_next += len(d)
                    elif t.seq > self.rx_next:
                        self.pending[t.seq] = payload
                self.ack = max(self.ack, self.rx_next or 0)
                send(self._base("A"), iface=self.iface)
            if t.flags & 0x01:  # FIN
                self.got_fin = True
                with_fin_ack = (self.rx_next or t.seq) + 1
                self.ack = max(self.ack, with_fin_ack)
                send(self._base("A"), iface=self.iface)

    def start(self):
        f = (
            f"tcp and src host {self.dst} and src port {self.dport} "
            f"and dst port {self.sport}"
        )
        self.sniffer = AsyncSniffer(
            filter=f, prn=self._on, store=False, iface=self.iface
        )
        self.sniffer.start()
        time.sleep(0.6)

    def stop(self):
        if self.sniffer:
            try:
                self.sniffer.stop()
            except Exception:
                pass

    # ---------- protocol ----------
    def connect(self, timeout=8):
        send(self._base("S"), iface=self.iface)
        if not self.syn_ack.wait(timeout):
            raise RuntimeError("no SYN-ACK (fragments or RST filtering issue?)")
        self.seq += 1
        send(self._base("A"), iface=self.iface)
        return True

    def send_data(self, payload, fragsize=None, gap=0.02):
        pkt = self._base("PA") / Raw(load=payload)
        if fragsize:
            frags = fragment(pkt, fragsize=fragsize)
            self.log(f"  sending {len(payload)}B as {len(frags)} IP fragments")
            for f in frags:
                send(f, iface=self.iface)
                time.sleep(gap)
        else:
            send(pkt, iface=self.iface)
        self.seq += len(payload)

    def send_decoy_then_real(self, decoy, real, gap=0.05):
        """Bad-checksum decoy at the same seq, then the real segment."""
        assert len(decoy) == len(real)
        bad = self._base("PA") / Raw(load=decoy)
        bad[TCP].chksum = 0x1234  # deliberately wrong -> Linux drops it
        send(bad, iface=self.iface)
        time.sleep(gap)
        send(self._base("PA") / Raw(load=real), iface=self.iface)
        self.seq += len(real)

    def recv_until(self, marker=b"\r\n\r\n", timeout=10):
        end = time.time() + timeout
        while time.time() < end:
            with self.lock:
                buf = self.rxbuf
                rst = self.got_rst
            if rst:
                raise RuntimeError("connection reset")
            if marker in buf:
                # if there's a content-length, wait for the body too
                try:
                    head, rest = buf.split(b"\r\n\r\n", 1)
                    cl = 0
                    for line in head.split(b"\r\n"):
                        if line.lower().startswith(b"content-length:"):
                            cl = int(line.split(b":", 1)[1].strip())
                    if len(rest) >= cl:
                        return buf
                except Exception:
                    return buf
            time.sleep(0.05)
        with self.lock:
            return self.rxbuf

    def close(self):
        try:
            send(self._base("FA"), iface=self.iface)
            self.seq += 1
            time.sleep(1.0)
            send(self._base("A"), iface=self.iface)
        except Exception:
            pass
