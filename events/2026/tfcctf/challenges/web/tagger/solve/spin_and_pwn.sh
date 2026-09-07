#!/bin/bash
# Wait for one of the three team instance slots to free up, take it for tagger,
# wait until the app answers, then run the exploit.
set -u
CH=$CH
CATCH="${CATCH:-https://postcard-foot-additionally-block.trycloudflare.com}"
MGR=https://challenge-manager.management.ctf.thefewchosen.com/isolated
NAME=""

# Plain read. Do NOT call ctf.relogin_quietly() here: it goes to `pass`, which
# can block on gpg-agent for a minute, and a re-login rotates the refresh token
# out from under the other agents sharing this token file. refresh_access() is
# safe and only fires when the JWT exp is within 90 s.
tok() {
  /usr/bin/python3 -c "
import json,sys
sys.path.insert(0,'$HOME/.claude/scripts')
try:
    import ctf
    if ctf.token_expiring():
        ctf.refresh_access()
except Exception:
    pass
print(json.load(open('$HOME/.config/ctf/token.json'))['token'])
" 2>/dev/null | tail -1
}

for i in $(seq 1 300); do
  T=$(tok)
  OUT=$(curl -s -H "Authorization: Bearer $T" -X POST "$MGR" \
        -H 'content-type: application/json' -d '{"name":"tagger"}' --max-time 60)
  echo "[$(date -u +%H:%M:%S)] spin($i): $OUT"
  NAME=$(printf '%s' "$OUT" | grep -oE 'tagger-[0-9a-f]+' | head -1)
  if [ -n "$NAME" ]; then
    printf '%s\n' "$OUT" > "$CH/artifacts/instance.json"
    break
  fi
  sleep 18
done

[ -z "$NAME" ] && { echo "never got a slot"; exit 1; }
URL="https://$NAME.challs.ctf.thefewchosen.com"   # plain http 308s to https
echo "[$(date -u +%H:%M:%S)] url: $URL"

for i in $(seq 1 60); do
  C=$(curl -s -o /dev/null -w '%{http_code}' "$URL/login" --max-time 20)
  echo "[$(date -u +%H:%M:%S)] $URL/login -> $C"
  [ "$C" = "200" ] && break
  sleep 4
done

cd "$CH" || exit 1
exec ctf-python solve/solve.py "$URL" --catch "$CATCH" --minutes 14 \
     --artifacts artifacts
