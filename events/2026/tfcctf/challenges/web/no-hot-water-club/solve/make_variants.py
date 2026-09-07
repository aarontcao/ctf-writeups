#!/usr/bin/env python3
"""
Build one context's KV cache blob under several CPU numeric regimes.

Insurance for the case where the recovered context is right but the digest is
still rejected, which means the remote host reaches a different fp32 kernel than
this AVX2-only VM. Runs make_blob.py inside the challenge container once per
environment and reports the distinct digests.

Usage: ctf-python solve/make_variants.py "<context>" [outdir]
"""
import json
import os
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
SCRATCH = os.path.join(ROOT, "scratch")
CONTAINER = "nohotwater-local"

REGIMES = [
    {},
    {"MKL_CBWR": "COMPATIBLE"},
    {"MKL_CBWR": "SSE4_2"},
    {"MKL_CBWR": "AVX"},
    {"MKL_CBWR": "AVX2"},
    {"ATEN_CPU_CAPABILITY": "default"},
    {"ATEN_CPU_CAPABILITY": "avx2"},
    {"TORCH_THREADS": "1"},
    {"TORCH_THREADS": "2"},
    {"TORCH_THREADS": "8"},
    {"MKLDNN_VERBOSE": "0", "TORCH_MKLDNN_ENABLED": "0"},
]


def main():
    context = sys.argv[1]
    out_dir = sys.argv[2] if len(sys.argv) > 2 else os.path.join(SCRATCH, "variants")
    os.makedirs(out_dir, exist_ok=True)
    req = os.path.join(SCRATCH, "req_variant.json")
    json.dump({"context": context}, open(req, "w"), ensure_ascii=False)
    subprocess.run(["docker", "cp", os.path.join(HERE, "make_blob.py"),
                    f"{CONTAINER}:/tmp/make_blob.py"], check=True)
    subprocess.run(["docker", "cp", req, f"{CONTAINER}:/tmp/reqv.json"], check=True)
    seen = {}
    for n, regime in enumerate(REGIMES):
        args = ["docker", "exec", "-e", "HF_HOME=/models"]
        for key, value in regime.items():
            args += ["-e", f"{key}={value}"]
        args += [CONTAINER, "python", "/tmp/make_blob.py", "/tmp/reqv.json", "/tmp/outv.json"]
        run = subprocess.run(args, capture_output=True, text=True)
        if run.returncode != 0:
            print(f"[!] {regime} failed: {run.stderr[-200:]}", flush=True)
            continue
        dst = os.path.join(out_dir, f"{n}.json")
        subprocess.run(["docker", "cp", f"{CONTAINER}:/tmp/outv.json", dst], check=True)
        digest = json.load(open(dst))["digest"]
        seen.setdefault(digest, []).append(regime)
        print(f"[+] {n} {regime} -> {digest}", flush=True)
    print(f"[=] {len(seen)} distinct digests across {len(REGIMES)} regimes", flush=True)
    json.dump({d: r for d, r in seen.items()},
              open(os.path.join(out_dir, "summary.json"), "w"), default=str)


if __name__ == "__main__":
    main()
