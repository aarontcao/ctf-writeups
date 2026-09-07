#!/usr/bin/env python3

import os
import secrets
import string

MAX_QUERIES = 195
PASSWORD_LENGTH = 30

ALPHABET = string.digits + string.ascii_uppercase + string.ascii_lowercase
FLAG = os.environ.get("FLAG", "TFCCTF{no1_s0_3asy}")


def generate_password():
    return "".join(secrets.choice(ALPHABET) for _ in range(PASSWORD_LENGTH))


def real_answer(guess, password):
    if guess == password:
        return "equal"
    if guess < password:
        return "smaller"
    return "larger"


def main():
    password = generate_password()
    switch_at = secrets.randbelow(MAX_QUERIES + 1)

    mood = 0

    print("Find the secret.")
    print(f"length = {PASSWORD_LENGTH}")
    print(f"queries = {MAX_QUERIES}")

    for query_id in range(MAX_QUERIES):

        if query_id == switch_at:
            mood = 1

        try:
            line = input("> ").strip()
        except EOFError:
            return

        parts = line.split(maxsplit=1)

        if len(parts) != 2:
            print("usage: <state> <guess>")
            continue

        state_raw, guess = parts

        if state_raw not in ("0", "1"):
            print("invalid")
            continue

        state = int(state_raw)

        if not guess or len(guess) > PASSWORD_LENGTH:
            print("invalid")
            continue

        if any(c not in ALPHABET for c in guess):
            print("invalid")
            continue

        truth = real_answer(guess, password)

        if state == mood:
            print(truth)

            if truth == "equal":
                print(FLAG)
                return

        else:
            print(secrets.choice(("smaller", "larger")))

    print("out of queries")


if __name__ == "__main__":
    main()