#!/usr/bin/env bash
# Resumable ordered sweep of scratch/allflags.txt.
#
# Usage:
#   sweep_all.sh              run from the checkpoint, no cap
#   sweep_all.sh 12400        run at most 12400 more submissions this invocation
#   sweep_all.sh 12400 0.5    ... at 0.5 s between submissions
CH="$(cd "$(dirname "${BASH_SOURCE[0]:-$0}")/.." && pwd)"
set -u

BASE=$CH
SLUG=fishing-not-phishing
LIST="$BASE/scratch/allflags.txt"
CKPT="$BASE/scratch/allflags.progress"
HITFILE="$BASE/scratch/allflags.hit"

MAXN="${1:-0}"          # 0 means no cap
DELAY="${2:-0.3}"

[ -s "$LIST" ] || { echo "no flag list at $LIST" >&2; exit 1; }

total=$(wc -l <"$LIST")
start=0
[ -f "$CKPT" ] && start=$(cat "$CKPT")

echo "list $total flags, resuming at line $((start + 1)), delay ${DELAY}s"
[ "$MAXN" -gt 0 ] && echo "cap $MAXN this run"
echo

i="$start"
done_now=0
t0=$(date +%s)

while IFS= read -r flag; do
  i=$((i + 1))
  [ -z "$flag" ] && continue

  out=$(ctf submit "$SLUG" --flag "$flag" --yes 2>&1)

  if ! echo "$out" | grep -qE 'NOT ACCEPTED|invalid_flag|incorrect'; then
    echo "$flag" >"$HITFILE"
    printf '\n[%d/%d] NOT A REJECTION, stopping for inspection\n' "$i" "$total"
    printf '        flag: %s\n' "$flag"
    echo "$out"
    echo "$i" >"$CKPT"
    exit 0
  fi

  done_now=$((done_now + 1))
  if [ $((i % 100)) -eq 0 ]; then
    echo "$i" >"$CKPT"
    el=$(( $(date +%s) - t0 ))
    [ "$el" -eq 0 ] && el=1
    rate=$(awk -v d="$done_now" -v e="$el" 'BEGIN{printf "%.1f", d/e}')
    printf '[%6d/%6d] %s/s  last: %s\n' "$i" "$total" "$rate" "$flag"
  fi

  if [ "$MAXN" -gt 0 ] && [ "$done_now" -ge "$MAXN" ]; then
    echo "$i" >"$CKPT"
    echo
    echo "=== cap reached: $done_now submitted this run, stopped at line $i ==="
    exit 2
  fi

  sleep "$DELAY"
done < <(tail -n +$((start + 1)) "$LIST")

echo "$i" >"$CKPT"
echo
echo "=== list exhausted: $done_now submitted this run, all rejected ==="
