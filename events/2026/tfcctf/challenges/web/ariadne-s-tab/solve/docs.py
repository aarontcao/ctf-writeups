#!/usr/bin/env python3
"""
docs: mirror of document-crypto.js in Python, plus upload/open helpers.
"""

import base64
import json
import os
import sys

from cryptography.hazmat.primitives import hashes, serialization
from cryptography.hazmat.primitives.asymmetric import padding, rsa
from cryptography.hazmat.primitives.ciphers.aead import AESGCM

import ari

OAEP = padding.OAEP(
    mgf=padding.MGF1(algorithm=hashes.SHA256()),
    algorithm=hashes.SHA256(),
    label=None,
)


def gen_keypair():
    key = rsa.generate_private_key(public_exponent=65537, key_size=3072)
    pkcs8 = key.private_bytes(
        serialization.Encoding.DER,
        serialization.PrivateFormat.PKCS8,
        serialization.NoEncryption(),
    )
    spki = key.public_key().public_bytes(
        serialization.Encoding.DER, serialization.PublicFormat.SubjectPublicKeyInfo
    )
    return {
        "privateKey": base64.b64encode(pkcs8).decode(),
        "publicKey": base64.b64encode(spki).decode(),
    }


def load_private(pkcs8_b64):
    return serialization.load_der_private_key(base64.b64decode(pkcs8_b64), None)


def load_public(spki_b64):
    return serialization.load_der_public_key(base64.b64decode(spki_b64))


def encrypt_file(data, spki_b64):
    aes = os.urandom(32)
    iv = os.urandom(12)
    ciphertext = AESGCM(aes).encrypt(iv, data, None)
    wrapped = load_public(spki_b64).encrypt(aes, OAEP)
    return {
        "ciphertext": base64.b64encode(ciphertext).decode(),
        "iv": base64.b64encode(iv).decode(),
        "wrapped_key": base64.b64encode(wrapped).decode(),
        "aes": aes,
    }


def b64url(raw):
    return base64.urlsafe_b64encode(raw).rstrip(b"=").decode()


def ensure_keys(state):
    if "keys" not in state:
        state["keys"] = gen_keypair()
        ari.save_state(state)
    return state["keys"]


def upload(state, name, mime, data):
    token = state["access_token"]
    keys = ensure_keys(state)
    status, body, _ = ari.api("key/register", token, {"public_key": keys["publicKey"]})
    if status not in (200, 201):
        raise SystemExit(f"key/register {status}: {body}")
    enc = encrypt_file(data, keys["publicKey"])
    status, body, _ = ari.api(
        "documents/create",
        token,
        {
            "name": name,
            "mime_type": mime,
            "ciphertext": enc["ciphertext"],
            "iv": enc["iv"],
            "wrapped_key": enc["wrapped_key"],
        },
    )
    if status not in (200, 201):
        raise SystemExit(f"documents/create {status}: {body}")
    return body, enc


def viewer_url(state, document_id):
    token = state["access_token"]
    status, body, _ = ari.api("documents/open", token, {"id": document_id})
    if status != 200:
        raise SystemExit(f"documents/open {status}: {body}")
    priv = load_private(state["keys"]["privateKey"])
    aes = priv.decrypt(base64.b64decode(body["wrapped_key"]), OAEP)
    return f"{ari.CONTENT}/viewer.html#" + "&".join(
        [f"cap={body['cap']}", f"key={b64url(aes)}"]
    )


if __name__ == "__main__":
    state = ari.load_state()
    if sys.argv[1:] and sys.argv[1] == "list":
        print(json.dumps(ari.api("documents/list", state["access_token"], {})[1], indent=2))
