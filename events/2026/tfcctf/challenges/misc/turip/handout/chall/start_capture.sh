#!/bin/bash
set -euo pipefail

POSTGRES_USER="tulip"
POSTGRES_DB="tulip"
POSTGRES_PASS="tulip"

SCHEMA_DIR="/tulip/schema"
TRAFFIC_DIR="/traffic"
TIMESCALE="postgres://${POSTGRES_USER}:${POSTGRES_PASS}@127.0.0.1:5432/${POSTGRES_DB}"
CAPTURE_ROTATION_SECONDS="${CAPTURE_ROTATION_SECONDS:-15}"

if [[ ! "${CAPTURE_ROTATION_SECONDS}" =~ ^[0-9]+$ ]] ||
   (( CAPTURE_ROTATION_SECONDS < 5 )); then
    echo "CAPTURE_ROTATION_SECONDS must be an integer of at least 5" >&2
    exit 1
fi

# Start tcpdump
nohup tcpdump \
    -Z root \
    -i any \
    -G "${CAPTURE_ROTATION_SECONDS}" \
    -w "${TRAFFIC_DIR}/capture-%Y%m%d-%H%M%S.pcap.tmp" \
    -z /usr/local/bin/finish-pcap \
    port 1337 \
    >/tcpdump.log 2>&1 &

# Start assembler
nohup /tulip/go-importer/assembler \
    -skipchecksum \
    -disable-converters \
    -dir "${TRAFFIC_DIR}" \
    -timescale "${TIMESCALE}" \
    >/assembler.log 2>&1 &
