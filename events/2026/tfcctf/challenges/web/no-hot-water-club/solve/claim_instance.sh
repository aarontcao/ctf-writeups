#!/bin/bash
# Poll the challenge manager until a slot frees, then claim one for this challenge.
CH="$(cd "$(dirname "${BASH_SOURCE[0]:-$0}")/.." && pwd)"
TOK=$(python3 -c "import json;print(json.load(open('$HOME/.config/ctf/token.json'))['token'])")
OUT=$CH/scratch/instance.json
for i in $(seq 1 400); do
  R=$(curl -s -X POST https://challenge-manager.management.ctf.thefewchosen.com/isolated \
        -H 'content-type: application/json' -H "Authorization: Bearer $TOK" \
        -d '{"name":"no-hot-water-team"}' --max-time 120)
  echo "$(date -u +%FT%TZ) $R"
  if ! grep -q '"error"' <<<"$R"; then echo "$R" > "$OUT"; echo CLAIMED; exit 0; fi
  sleep 20
done
exit 1
