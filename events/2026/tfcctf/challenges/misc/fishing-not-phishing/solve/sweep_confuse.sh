#!/usr/bin/env bash
# Sweep every flag string in scratch/confuse_flags.txt.
CH="$(cd "$(dirname "${BASH_SOURCE[0]:-$0}")/.." && pwd)"
set -u
SLUG=fishing-not-phishing
LIST="${1:-$CH/scratch/confuse_flags.txt}"

if [ ! -s "$LIST" ]; then
  echo "no flag list at $LIST" >&2
  exit 1
fi

total=$(wc -l <"$LIST")
echo "sweeping $total flags from $LIST"
echo

n=0
while IFS= read -r flag; do
  [ -z "$flag" ] && continue
  n=$((n + 1))
  out=$(ctf submit "$SLUG" --flag "$flag" --yes 2>&1)
  if echo "$out" | grep -qE 'NOT ACCEPTED|invalid_flag|incorrect'; then
    printf '[%03d/%03d] rejected  %s\n' "$n" "$total" "$flag"
    sleep 0.5
    continue
  fi
  printf '\n[%03d/%03d] NOT A REJECTION, stopping for inspection\n' "$n" "$total"
  printf '          flag: %s\n' "$flag"
  echo "$out"
  exit 0
done <"$LIST"

echo
echo "=== all $n rejected ==="
