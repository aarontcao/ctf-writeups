#!/bin/bash
set -euo pipefail

if [[ -z "${SESSION_SECRET:-}" ]]; then
    echo 'Set a persistent session signing secret, for example:' >&2
    echo '  export SESSION_SECRET="$(openssl rand -hex 32)"' >&2
    exit 1
fi

if [[ -z "${FLAG:-}" ]]; then
    echo 'Set FLAG before starting the challenge.' >&2
    exit 1
fi

docker build -t turip_chall .
docker run -it --rm \
    -p 1337:1337 \
    -e SESSION_SECRET \
    -e FLAG \
    -e TEAM_AUTH_URL="${TEAM_AUTH_URL:-https://api.ctf.thefewchosen.com/team/token}" \
    -e TEAM_AUTH_TIMEOUT="${TEAM_AUTH_TIMEOUT:-5}" \
    -e RATE_LIMIT_SECONDS="${RATE_LIMIT_SECONDS:-10}" \
    -e AUTH_RATE_LIMIT_SECONDS="${AUTH_RATE_LIMIT_SECONDS:-2}" \
    -e AUTH_MAX_CONCURRENT="${AUTH_MAX_CONCURRENT:-8}" \
    -e MARKER_WINDOW_SECONDS="${MARKER_WINDOW_SECONDS:-120}" \
    -e SESSION_LIFETIME_SECONDS="${SESSION_LIFETIME_SECONDS:-7200}" \
    -e SESSION_COOKIE_SECURE="${SESSION_COOKIE_SECURE:-false}" \
    -e TRAFFIC_RETENTION_MINUTES="${TRAFFIC_RETENTION_MINUTES:-60}" \
    -e PCAP_RETENTION_MINUTES="${PCAP_RETENTION_MINUTES:-60}" \
    turip_chall
