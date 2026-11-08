import hashlib
import math
import os
import re
import threading
import time
import uuid
from collections import OrderedDict
from datetime import timedelta
from functools import wraps

from flask import Flask, g, jsonify, request, session
import psycopg
import requests

app = Flask(__name__)

FLAG = os.getenv("FLAG", "TFCCTF{fake_flag}")
SESSION_SECRET = os.getenv("SESSION_SECRET")

if not SESSION_SECRET or len(SESSION_SECRET) < 32:
    raise RuntimeError("SESSION_SECRET must contain at least 32 characters")


def env_bool(name, default):
    value = os.getenv(name)
    if value is None:
        return default
    return value.lower() in {"1", "true", "yes", "on"}


app.secret_key = SESSION_SECRET
app.config.update(
    SESSION_COOKIE_NAME="turip_session",
    SESSION_COOKIE_HTTPONLY=True,
    SESSION_COOKIE_SECURE=env_bool("SESSION_COOKIE_SECURE", False),
    SESSION_COOKIE_SAMESITE="Lax",
    SESSION_REFRESH_EACH_REQUEST=False,
    PERMANENT_SESSION_LIFETIME=timedelta(
        seconds=int(os.getenv("SESSION_LIFETIME_SECONDS", "7200"))
    ),
    MAX_CONTENT_LENGTH=int(os.getenv("MAX_CONTENT_LENGTH", "8192")),
)

DB_URI = os.getenv(
    "DB_URI",
    "postgresql://tulip:tulip@127.0.0.1:5432/tulip",
)
CANONICAL_FLAG_PATH = "/get_flag1337"
CANONICAL_FLAG_BODY = (
    b'{"supersecretkey":"turip_ip_ip","ip":"1337.0.0.1"}'
)
NEEDLES = [
    b"get_flag1337",
    b"turip_ip_ip",
    b"1337.0.0.1",
    b"GET /get_flag1337",
    b"POST /get_flag1337",
]
TRAFFIC_BARRIER_HEADER = "X-Traffic-Barrier"
TEAM_AUTH_URL = os.getenv(
    "TEAM_AUTH_URL",
    "https://api.ctf.thefewchosen.com/team/token",
)
TEAM_AUTH_TIMEOUT = float(os.getenv("TEAM_AUTH_TIMEOUT", "5"))
RATE_LIMIT_SECONDS = float(os.getenv("RATE_LIMIT_SECONDS", "10"))
AUTH_RATE_LIMIT_SECONDS = float(os.getenv("AUTH_RATE_LIMIT_SECONDS", "2"))
AUTH_MAX_CONCURRENT = int(os.getenv("AUTH_MAX_CONCURRENT", "8"))
AUTH_TRACKED_CLIENTS = int(os.getenv("AUTH_TRACKED_CLIENTS", "4096"))
MARKER_WINDOW_SECONDS = float(os.getenv("MARKER_WINDOW_SECONDS", "120"))
TOKEN_PATTERN = re.compile(r"^[0-9a-fA-F]{1,256}$")

if TEAM_AUTH_TIMEOUT <= 0:
    raise RuntimeError("TEAM_AUTH_TIMEOUT must be greater than zero")
if RATE_LIMIT_SECONDS < 0:
    raise RuntimeError("RATE_LIMIT_SECONDS cannot be negative")
if AUTH_RATE_LIMIT_SECONDS < 0:
    raise RuntimeError("AUTH_RATE_LIMIT_SECONDS cannot be negative")
if AUTH_MAX_CONCURRENT < 1:
    raise RuntimeError("AUTH_MAX_CONCURRENT must be at least one")
if AUTH_TRACKED_CLIENTS < 1:
    raise RuntimeError("AUTH_TRACKED_CLIENTS must be at least one")
if MARKER_WINDOW_SECONDS <= 0:
    raise RuntimeError("MARKER_WINDOW_SECONDS must be greater than zero")

AUTH_LAST_REQUEST_AT = OrderedDict()
AUTH_RATE_LOCK = threading.Lock()
AUTH_CONCURRENCY = threading.BoundedSemaphore(AUTH_MAX_CONCURRENT)


def no_store(response):
    response.headers["Cache-Control"] = "no-store"
    response.headers["Pragma"] = "no-cache"
    response.headers["Expires"] = "0"
    return response


@app.after_request
def protect_sensitive_responses(response):
    if request.path in {
        "/auth",
        "/logout",
        "/restart",
        "/check",
        CANONICAL_FLAG_PATH,
    }:
        no_store(response)
    return response


def consume_auth_rate_limit(client_id):
    """Return the number of seconds left, or zero when the request is allowed."""
    if AUTH_RATE_LIMIT_SECONDS == 0:
        return 0.0

    now = time.monotonic()
    with AUTH_RATE_LOCK:
        last_request = AUTH_LAST_REQUEST_AT.get(client_id)
        if last_request is not None:
            remaining = AUTH_RATE_LIMIT_SECONDS - (now - last_request)
            if remaining > 0:
                AUTH_LAST_REQUEST_AT.move_to_end(client_id)
                return remaining

        AUTH_LAST_REQUEST_AT[client_id] = now
        AUTH_LAST_REQUEST_AT.move_to_end(client_id)
        while len(AUTH_LAST_REQUEST_AT) > AUTH_TRACKED_CLIENTS:
            AUTH_LAST_REQUEST_AT.popitem(last=False)

    return 0.0


def consume_team_rate_limit(team_id):
    """Atomically consume the team's shared database-backed rate limit."""
    if RATE_LIMIT_SECONDS == 0:
        return 0.0

    query = """
        INSERT INTO challenge_team_rate_limit (team_id, next_allowed_at)
        VALUES (%s, now() + make_interval(secs => %s))
        ON CONFLICT (team_id) DO UPDATE
        SET next_allowed_at = EXCLUDED.next_allowed_at
        WHERE challenge_team_rate_limit.next_allowed_at <= now()
        RETURNING next_allowed_at
    """
    with psycopg.connect(DB_URI, autocommit=True) as conn:
        with conn.cursor() as cur:
            cur.execute(query, (team_id, RATE_LIMIT_SECONDS))
            if cur.fetchone() is not None:
                return 0.0

            cur.execute(
                """
                SELECT GREATEST(
                    EXTRACT(EPOCH FROM next_allowed_at - now()),
                    0
                )::double precision
                FROM challenge_team_rate_limit
                WHERE team_id = %s
                """,
                (team_id,),
            )
            row = cur.fetchone()
            return float(row[0]) if row is not None else 0.0


def save_team_attempt(team_id, attempt_id):
    with psycopg.connect(DB_URI, autocommit=True) as conn:
        with conn.cursor() as cur:
            cur.execute(
                """
                INSERT INTO challenge_team_state (team_id, attempt_id, created_at)
                VALUES (%s, %s::uuid, now())
                ON CONFLICT (team_id) DO UPDATE
                SET attempt_id = EXCLUDED.attempt_id,
                    created_at = EXCLUDED.created_at
                RETURNING EXTRACT(EPOCH FROM created_at)::bigint
                """,
                (team_id, attempt_id),
            )
            return int(cur.fetchone()[0])


def load_team_attempt(team_id):
    with psycopg.connect(DB_URI, autocommit=True) as conn:
        with conn.cursor() as cur:
            cur.execute(
                """
                SELECT attempt_id::text,
                       EXTRACT(EPOCH FROM created_at)::bigint
                FROM challenge_team_state
                WHERE team_id = %s
                """,
                (team_id,),
            )
            row = cur.fetchone()
            if row is None:
                return None
            return {"id": row[0], "timestamp": int(row[1])}


def reset_team_attempt(team_id):
    with psycopg.connect(DB_URI, autocommit=True) as conn:
        with conn.cursor() as cur:
            cur.execute(
                "DELETE FROM challenge_team_state WHERE team_id = %s",
                (team_id,),
            )


def authenticated_team_endpoint(view):
    @wraps(view)
    def wrapped(*args, **kwargs):
        team_id = session.get("team_id")
        team_name = session.get("team_name")
        if (
            not isinstance(team_id, str)
            or not re.fullmatch(r"[0-9a-f]{64}", team_id)
            or not isinstance(team_name, str)
            or not team_name
        ):
            return jsonify(
                status="error",
                message="authentication required",
            ), 401

        remaining = consume_team_rate_limit(team_id)
        if remaining > 0:
            response = jsonify(
                status="error",
                message="rate limit exceeded",
                retry_after=math.ceil(remaining),
            )
            response.headers["Retry-After"] = str(math.ceil(remaining))
            return response, 429

        g.team_id = team_id
        g.team_name = team_name
        return view(*args, **kwargs)

    return wrapped


@app.get("/")
def index():
    return "Hello"


@app.get("/health")
def health():
    return jsonify(status="ok")


@app.post("/auth")
def authenticate_team():
    client_id = request.remote_addr or "unknown"
    remaining = consume_auth_rate_limit(client_id)
    if remaining > 0:
        response = jsonify(
            status="error",
            message="authentication rate limit exceeded",
            retry_after=math.ceil(remaining),
        )
        response.headers["Retry-After"] = str(math.ceil(remaining))
        return response, 429

    data = request.get_json(silent=True)
    token = data.get("token") if isinstance(data, dict) else None
    if not isinstance(token, str) or not TOKEN_PATTERN.fullmatch(token):
        return jsonify(status="error", message="token must be a hex string"), 400

    if not AUTH_CONCURRENCY.acquire(blocking=False):
        response = jsonify(
            status="error",
            message="authentication service busy; retry shortly",
        )
        response.headers["Retry-After"] = "1"
        return response, 503

    try:
        try:
            upstream = requests.post(
                TEAM_AUTH_URL,
                json={"token": token},
                headers={"Accept": "application/json", "Connection": "close"},
                timeout=TEAM_AUTH_TIMEOUT,
                allow_redirects=False,
            )
        except requests.RequestException:
            app.logger.exception("team authentication service request failed")
            return jsonify(
                status="error",
                message="authentication service unavailable",
            ), 502
    finally:
        AUTH_CONCURRENCY.release()

    if upstream.status_code != 200:
        app.logger.error(
            "team authentication service returned HTTP %s",
            upstream.status_code,
        )
        return jsonify(status="error", message="authentication service unavailable"), 502

    try:
        upstream_data = upstream.json()
    except ValueError:
        app.logger.error("team authentication service returned invalid JSON")
        return jsonify(status="error", message="authentication service unavailable"), 502

    if upstream_data is None:
        session.clear()
        return jsonify(status="error", message="invalid team token"), 401

    team_name = upstream_data.get("name") if isinstance(upstream_data, dict) else None
    if not isinstance(team_name, str) or not team_name:
        app.logger.error("team authentication service response has no team name")
        return jsonify(status="error", message="authentication service unavailable"), 502

    # The validated token is the unique team credential. Hash its normalized
    # representation so duplicate or renamed team names cannot share state.
    team_id = hashlib.sha256(token.lower().encode("ascii")).hexdigest()
    session.clear()
    session["team_id"] = team_id
    session["team_name"] = team_name
    session.permanent = True

    response = jsonify(name=team_name)
    return response


@app.post("/logout")
def logout():
    session.clear()
    return jsonify(status="ok")


@app.post("/restart")
@authenticated_team_endpoint
def restart():
    # A shared instance must never restart capture or truncate global traffic.
    reset_team_attempt(g.team_id)

    return jsonify(status="ok, team challenge state reset")


def check_traffic_barrier(aux_id, attempt_timestamp):
    """Check one DB snapshot after Tulip has completed the marked flow."""
    marker = f"{TRAFFIC_BARRIER_HEADER}: {aux_id}".encode()
    needle_predicate = " OR ".join(
        "position(%s::bytea IN stream.data) > 0" for _ in NEEDLES
    )
    query = f"""
        WITH bounds AS MATERIALIZED (
            SELECT
                fid_pack_low(
                    to_timestamp(%s) - interval '5 seconds'
                ) AS lower_id,
                fid_pack_high(
                    to_timestamp(%s) + make_interval(secs => %s)
                ) AS upper_id
        ),
        completed_server_streams AS MATERIALIZED (
            SELECT
                marker_item.flow_id,
                string_agg(
                    marker_item.data,
                    ''::bytea
                    ORDER BY marker_item.id
                ) AS data
            FROM flow_item AS marker_item
            INNER JOIN flow AS completed_flow
                ON completed_flow.id = marker_item.flow_id
            CROSS JOIN bounds
            WHERE marker_item.direction = 's'
              AND marker_item.id >= bounds.lower_id
              AND marker_item.id <= bounds.upper_id
            GROUP BY marker_item.flow_id
        ),
        marker_flows AS MATERIALIZED (
            SELECT server_stream.flow_id
            FROM completed_server_streams AS server_stream
            WHERE position(%s::bytea IN server_stream.data) > 0
        ),
        client_streams AS MATERIALIZED (
            SELECT
                item.flow_id,
                string_agg(item.data, ''::bytea ORDER BY item.id) AS data
            FROM flow_item AS item
            INNER JOIN marker_flows AS marker
                ON marker.flow_id = item.flow_id
            WHERE item.direction = 'c'
            GROUP BY item.flow_id
        )
        SELECT
            EXISTS (SELECT 1 FROM marker_flows) AS marker_seen,
            EXISTS (
                SELECT 1
                FROM client_streams AS stream
                WHERE ({needle_predicate})
            ) AS forbidden_seen
    """
    with psycopg.connect(DB_URI, autocommit=True) as conn:
        with conn.cursor() as cur:
            cur.execute(
                query,
                (
                    attempt_timestamp,
                    attempt_timestamp,
                    MARKER_WINDOW_SECONDS,
                    marker,
                    *NEEDLES,
                ),
            )
            return cur.fetchone()


@app.get("/check")
@authenticated_team_endpoint
def check():
    result = load_team_attempt(g.team_id)

    if result is None:
        return jsonify(
            status="error",
            message="brevski, go to /get_flag1337 first",
        ), 400

    aux_id = result.get("id")
    if not aux_id:
        return jsonify(status="error", message="brevski, ceva e sus af"), 400

    marker_seen, forbidden_seen = check_traffic_barrier(
        aux_id,
        result["timestamp"],
    )
    if not marker_seen:
        response = jsonify(
            status="error",
            message="traffic ingestion is still pending; retry /check",
        )
        response.headers["Retry-After"] = str(max(1, math.ceil(RATE_LIMIT_SECONDS)))
        return response, 503

    if forbidden_seen:
        return jsonify(
            status="error",
            message="forbidden request data was visible in your captured flow",
        ), 400

    # Do not return an older result if the same team started a new attempt
    # concurrently while its traffic status was being checked.
    current_result = load_team_attempt(g.team_id)
    if current_result is None or current_result.get("id") != aux_id:
        return jsonify(
            status="error",
            message="challenge state changed; retry /check",
        ), 409

    result["flag"] = FLAG
    return jsonify(status="brevski, na flegu... e bile sau nu e bile?", data=result)


@app.post("/get_flag1337")
@authenticated_team_endpoint
def get_flag():
    raw_target = request.environ.get("RAW_URI")
    if raw_target is None:
        raw_target = request.environ.get("REQUEST_URI")

    noncanonical_transport = (
        request.headers.get("Transfer-Encoding") is not None
        or request.headers.get("Content-Encoding") is not None
    )
    raw_body = request.get_data(cache=True, as_text=False)
    if (
        raw_target != CANONICAL_FLAG_PATH
        or noncanonical_transport
        or request.mimetype != "application/json"
        or request.content_length != len(CANONICAL_FLAG_BODY)
        or raw_body != CANONICAL_FLAG_BODY
    ):
        return jsonify(status="error", message="Invalid request"), 400

    aux_id = str(uuid.uuid4())

    save_team_attempt(g.team_id, aux_id)

    # The marker is captured in the response on the same TCP flow. /check also
    # requires Tulip's parent flow row, which is inserted only after every flow
    # item has completed insertion.
    response = jsonify(
        status="ok, let's see what you got",
        data="e bile sau nu e bile?",
    )
    response.headers[TRAFFIC_BARRIER_HEADER] = aux_id
    return response


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=1337, debug=False)
