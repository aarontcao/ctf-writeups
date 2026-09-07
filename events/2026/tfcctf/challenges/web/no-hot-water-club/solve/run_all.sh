#!/bin/bash
# End to end run once scratch/instance.json exists.
CH="$(cd "$(dirname "${BASH_SOURCE[0]:-$0}")/.." && pwd)"
set -x
D=$CH
cd "$D" || exit 1
URL=$(python3 -c "
import json,sys
d=json.load(open('$D/scratch/instance.json'))
print(d.get('url') or d.get('link') or json.dumps(d))
")
echo "URL=$URL"
curl -s --max-time 20 "$URL/health"; echo
$HOME/bin/ctf-python solve/solve.py headcheck "$URL" 2>&1 | tee -a artifacts/remote.log
$HOME/bin/ctf-python solve/solve.py recover  "$URL" 2>&1 | tee -a artifacts/remote.log
$HOME/bin/ctf-python solve/solve.py blob            2>&1 | tee -a artifacts/remote.log
$HOME/bin/ctf-python solve/solve.py audit    "$URL" 2>&1 | tee -a artifacts/remote.log
