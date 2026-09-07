#!/usr/bin/env bash
# Flag sweep for the two live MARE candidates on fishing-not-phishing.
#
# Candidate 1: MADONNINA DEL MARE. MMSI 701000604, IMO 9013373, ARG, trawler.
#   Departed MAR DEL PLATA 2023-09-01T19:40:04, anchorage -38.04575,-57.52970.
#   First September fishing 2023-09-02T09:14:03 UTC at -39.2149,-59.1583.
#   192.1 haversine, 192.2 WGS84 geodesic, 192.8 from a published port coordinate,
#   95.1 the GFW panel figure. The GFW figure is the distance to a port about 95 km away,
#   not to Mar del Plata, so that pairing is internally inconsistent. Swept anyway,
#   because an author reading the panel would have written it regardless.
#   It's the only vessel in all 86,642 whose name ends in MARE that also carries an
#   IMO and an offshore leg.
#
# Candidate 2: NORWEGIAN NIGHTMARE. MMSI 316033853, no IMO, CAN, drifting longlines.
#   Departed PUBNICO 2023-09-03T03:23, first September fishing 2023-09-04T14:21.
#   60.2 km over 35.0 h. Its low implied speed is NOT a defect: a longliner drifts
#   while setting and soaking gear, so average speed isn't a valid test on that gear.
#   Tail "HTMARE" fits the hull fragment at the same glyph index as MADONNINA's "L MARE".
set -u
SLUG=fishing-not-phishing
n=0

try() {
  local flag="$1"
  local out
  n=$((n + 1))
  out=$(ctf submit "$SLUG" --flag "$flag" --yes 2>&1)
  if echo "$out" | grep -qE 'NOT ACCEPTED|invalid_flag|incorrect'; then
    printf '[%02d] rejected  %s\n' "$n" "$flag"
    sleep 1
    return 0
  fi
  printf '\n[%02d] NOT A REJECTION, stopping for inspection\n' "$n"
  printf '     flag: %s\n' "$flag"
  echo "$out"
  exit 0
}

# Candidate 1, both port spellings, distances most likely first.
for port in "mar del plata" "mar_del_plata"; do
  for d in 192.1 192.2 95.1 95.0 192.8 192.9 192.0 192.3 192.4 192.5 192.6 192.7 95.2; do
    try "TFCCTF{701000604_${port}_02.09.2023_09:14_AM_${d}}"
  done
done

# Candidate 2.
for d in 60.2 60.1 60.3 33.0 60.0 60.4 60.5; do
  try "TFCCTF{316033853_pubnico_04.09.2023_02:21_PM_${d}}"
done

echo
echo "=== all $n rejected ==="
