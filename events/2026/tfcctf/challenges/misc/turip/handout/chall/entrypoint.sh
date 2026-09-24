#!/bin/bash
set -euo pipefail

POSTGRES_USER="tulip"
POSTGRES_DB="tulip"
POSTGRES_PASS="tulip"

SCHEMA_DIR="/tulip/schema"
TRAFFIC_DIR="/traffic"
TIMESCALE="postgres://${POSTGRES_USER}:${POSTGRES_PASS}@127.0.0.1:5432/${POSTGRES_DB}"
SESSION_SECRET="${SESSION_SECRET:-}"
FLAG="${FLAG:-}"
TRAFFIC_RETENTION_MINUTES="${TRAFFIC_RETENTION_MINUTES:-60}"
CLEANUP_INTERVAL_SECONDS="${CLEANUP_INTERVAL_SECONDS:-300}"
SESSION_LIFETIME_SECONDS="${SESSION_LIFETIME_SECONDS:-7200}"

if [[ -z "${SESSION_SECRET:-}" || ${#SESSION_SECRET} -lt 32 ]]; then
    echo "SESSION_SECRET must contain at least 32 characters" >&2
    exit 1
fi

if [[ -z "${FLAG:-}" ]]; then
    echo "FLAG must be set" >&2
    exit 1
fi

if [[ ! "${TRAFFIC_RETENTION_MINUTES}" =~ ^[0-9]+$ ]] ||
   (( TRAFFIC_RETENTION_MINUTES < 5 )); then
    echo "TRAFFIC_RETENTION_MINUTES must be an integer of at least 5" >&2
    exit 1
fi

if [[ ! "${CLEANUP_INTERVAL_SECONDS}" =~ ^[0-9]+$ ]] ||
   (( CLEANUP_INTERVAL_SECONDS < 30 )); then
    echo "CLEANUP_INTERVAL_SECONDS must be an integer of at least 30" >&2
    exit 1
fi

if [[ ! "${SESSION_LIFETIME_SECONDS}" =~ ^[0-9]+$ ]] ||
   (( SESSION_LIFETIME_SECONDS < 60 )); then
    echo "SESSION_LIFETIME_SECONDS must be an integer of at least 60" >&2
    exit 1
fi

service postgresql start

# Create/update tulip role
runuser -u postgres -- psql -v ON_ERROR_STOP=1 <<EOF
DO \$\$
BEGIN
    IF NOT EXISTS (
        SELECT 1 FROM pg_roles WHERE rolname = '${POSTGRES_USER}'
    ) THEN
        CREATE ROLE ${POSTGRES_USER}
            LOGIN
            PASSWORD '${POSTGRES_PASS}';
    ELSE
        ALTER ROLE ${POSTGRES_USER}
            WITH LOGIN
            PASSWORD '${POSTGRES_PASS}';
    END IF;
END
\$\$;
EOF

# Create database if missing
if ! runuser -u postgres -- psql -tAc \
    "SELECT 1 FROM pg_database WHERE datname='${POSTGRES_DB}'" | grep -q 1; then

    runuser -u postgres -- createdb \
        -O "${POSTGRES_USER}" \
        "${POSTGRES_DB}"
fi

# Enable TimescaleDB
runuser -u postgres -- psql \
    -d "${POSTGRES_DB}" \
    -v ON_ERROR_STOP=1 \
    -c "CREATE EXTENSION IF NOT EXISTS timescaledb;"

# Needs superuser privileges
runuser -u postgres -- psql \
    -d "${POSTGRES_DB}" \
    -v ON_ERROR_STOP=1 \
    -f "${SCHEMA_DIR}/system.sql"

# Contains LANGUAGE c functions, so also needs superuser
runuser -u postgres -- psql \
    -d "${POSTGRES_DB}" \
    -v ON_ERROR_STOP=1 \
    -f "${SCHEMA_DIR}/functions.sql"

# Create application tables as tulip so tulip owns them
PGPASSWORD="${POSTGRES_PASS}" psql \
    -h 127.0.0.1 \
    -U "${POSTGRES_USER}" \
    -d "${POSTGRES_DB}" \
    -v ON_ERROR_STOP=1 \
    -f "${SCHEMA_DIR}/schema.sql"

# Challenge state and rate limits live in PostgreSQL so application restarts
# and multiple Gunicorn workers cannot reset or bypass a team's state.
PGPASSWORD="${POSTGRES_PASS}" psql \
    -h 127.0.0.1 \
    -U "${POSTGRES_USER}" \
    -d "${POSTGRES_DB}" \
    -v ON_ERROR_STOP=1 <<'SQL'
CREATE TABLE IF NOT EXISTS challenge_team_state (
    team_id text PRIMARY KEY CHECK (team_id ~ '^[0-9a-f]{64}$'),
    attempt_id uuid NOT NULL,
    created_at timestamptz NOT NULL
);

CREATE TABLE IF NOT EXISTS challenge_team_rate_limit (
    team_id text PRIMARY KEY CHECK (team_id ~ '^[0-9a-f]{64}$'),
    next_allowed_at timestamptz NOT NULL
);
SQL

# Give tulip access to objects created by postgres
runuser -u postgres -- psql \
    -d "${POSTGRES_DB}" \
    -v ON_ERROR_STOP=1 <<EOF
GRANT USAGE ON SCHEMA public TO ${POSTGRES_USER};

GRANT ALL PRIVILEGES
ON ALL TABLES IN SCHEMA public
TO ${POSTGRES_USER};

GRANT ALL PRIVILEGES
ON ALL SEQUENCES IN SCHEMA public
TO ${POSTGRES_USER};

GRANT EXECUTE
ON ALL FUNCTIONS IN SCHEMA public
TO ${POSTGRES_USER};
EOF

mkdir -p "${TRAFFIC_DIR}"

# Rename completed captures from .pcap.tmp -> .pcap
cat >/usr/local/bin/finish-pcap <<'EOF'
#!/bin/bash
set -e

FILE="$1"

case "$FILE" in
    *.pcap.tmp)
        mv -- "$FILE" "${FILE%.tmp}"
        ;;
esac

RETENTION_MINUTES="${PCAP_RETENTION_MINUTES:-60}"
if [[ "${RETENTION_MINUTES}" =~ ^[0-9]+$ ]] &&
   (( RETENTION_MINUTES >= 5 )); then
    find /traffic \
        -type f \
        -name 'capture-*.pcap' \
        -mmin "+${RETENTION_MINUTES}" \
        -delete
fi
EOF

chmod +x /usr/local/bin/finish-pcap

/start_capture.sh &

cleanup_database_once() {
    PGPASSWORD="${POSTGRES_PASS}" psql \
        -h 127.0.0.1 \
        -U "${POSTGRES_USER}" \
        -d "${POSTGRES_DB}" \
        -v ON_ERROR_STOP=1 \
        -v retention_minutes="${TRAFFIC_RETENTION_MINUTES}" \
        -v session_lifetime="${SESSION_LIFETIME_SECONDS}" <<'SQL'
DELETE FROM flow_index
WHERE flow_id IN (
    SELECT id
    FROM flow
    WHERE time < now() - make_interval(mins => :retention_minutes)
);

SELECT drop_chunks(
    'flow_item',
    older_than => make_interval(mins => :retention_minutes)
);
SELECT drop_chunks(
    'flow',
    older_than => make_interval(mins => :retention_minutes)
);

DELETE FROM challenge_team_state
WHERE created_at < now() - make_interval(secs => :session_lifetime);
DELETE FROM challenge_team_rate_limit
WHERE next_allowed_at < now() - interval '1 day';
SQL
}

cleanup_database() {
    while true; do
        sleep "${CLEANUP_INTERVAL_SECONDS}"
        cleanup_database_once || echo "database cleanup failed; retrying later" >&2
    done
}

cleanup_database >/cleanup.log 2>&1 &

nohup bash -c 'while true; do sleep 10; curl -s http://localhost:1337/health > /dev/null; done' >/health.log 2>&1 &

exec gunicorn \
    --chdir / \
    --bind 0.0.0.0:1337 \
    --workers "${GUNICORN_WORKERS:-1}" \
    --threads "${GUNICORN_THREADS:-32}" \
    --backlog "${GUNICORN_BACKLOG:-256}" \
    --keep-alive 2 \
    --limit-request-line 1024 \
    --limit-request-fields 50 \
    --limit-request-field_size 4096 \
    --max-requests 10000 \
    --max-requests-jitter 1000 \
    --timeout 30 \
    app:app
