#!/bin/bash
# Claim an instance slot, fire the finished exploit, then release the slot
# immediately so the next agent in the queue gets it back within a minute.
#
# usage: pwn.sh            claim + solve + release
#        pwn.sh HOST PORT  solve against an instance somebody already started
set -u
DIR="$(cd "$(dirname "$0")" && pwd)"
TOKEN() { python3 -c "import json;print(json.load(open('$HOME/.config/ctf/token.json'))['token'])"; }
API=https://challenge-manager.management.ctf.thefewchosen.com/isolated

if [ $# -ge 2 ]; then
    python3 "$DIR/solve.py" "$1" "$2"
    exit $?
fi

R=$(curl -s -m 25 -H "Authorization: Bearer $(TOKEN)" -X POST "$API" \
        -H 'content-type: application/json' -d '{"name":"python-jail"}')
echo "claim: $R"
case "$R" in
  *error*|"") echo "no slot, not retrying"; exit 1;;
esac

HOST=$(printf '%s' "$R" | python3 -c "import sys,json;d=json.load(sys.stdin);print(d.get('host') or d.get('data',{}).get('host',''))")
PORT=$(printf '%s' "$R" | python3 -c "import sys,json;d=json.load(sys.stdin);print(d.get('port') or d.get('data',{}).get('port',''))")
NAME=$(printf '%s' "$R" | python3 -c "import sys,json;d=json.load(sys.stdin);print(d.get('name') or d.get('data',{}).get('name',''))")
echo "host=$HOST port=$PORT name=$NAME"

sleep 8   # let the pod come up
python3 "$DIR/solve.py" "$HOST" "$PORT" | tee "$DIR/../artifacts/remote-run.txt"

# release the slot straight away so the queue behind us moves
"$HOME/bin/ctf" instance stop the-pyjail 2>&1 | tail -3
curl -s -m 25 -H "Authorization: Bearer $(TOKEN)" -X DELETE "$API" \
     -H 'content-type: application/json' -d "{\"name\":\"$NAME\"}"
echo
