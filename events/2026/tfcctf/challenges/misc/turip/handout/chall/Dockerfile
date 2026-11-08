FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive
ARG TULIP_COMMIT=523e5179043a5b6ae1bbcc1990d774f23166319b
ARG PG_HINT_PLAN_COMMIT=ae701aa7f2d417672d70070be803e27a67e49a20

RUN apt update && apt install -y \
    wget \
    curl \
    git \
    build-essential \
    golang-go \
    make \
    libpcap-dev \
    python3 \
    python3-pip \
    python3-dev \
    gnupg \
    ca-certificates \
    postgresql-common \
    llvm-19 \
    clang-19 \
    tcpdump \
    net-tools 

# PostgreSQL 15 repo
RUN install -d /usr/share/postgresql-common/pgdg && \
    curl -o /usr/share/postgresql-common/pgdg/apt.postgresql.org.asc \
        --fail \
        https://www.postgresql.org/media/keys/ACCC4CF8.asc && \
    echo "deb [signed-by=/usr/share/postgresql-common/pgdg/apt.postgresql.org.asc] \
        https://apt.postgresql.org/pub/repos/apt noble-pgdg main" \
        > /etc/apt/sources.list.d/pgdg.list

RUN apt update && apt install -y \
    postgresql-15 \
    postgresql-client-15 \
    postgresql-server-dev-15

# TimescaleDB repository
RUN echo "deb https://packagecloud.io/timescale/timescaledb/ubuntu/ noble main" \
        > /etc/apt/sources.list.d/timescaledb.list && \
    wget -qO- https://packagecloud.io/timescale/timescaledb/gpgkey \
        | gpg --dearmor \
        > /etc/apt/trusted.gpg.d/timescaledb.gpg

RUN apt update && apt install -y \
    timescaledb-2-postgresql-15

RUN echo "shared_preload_libraries = 'timescaledb'" \
    >> /etc/postgresql/15/main/postgresql.conf

ENV PATH="/usr/lib/postgresql/15/bin:${PATH}"

WORKDIR /tulip

# Fetch the audited Tulip revision instead of following a moving branch.
RUN git init /tulip/tulip && \
    cd /tulip/tulip && \
    git remote add origin https://github.com/OpenAttackDefenseTools/tulip.git && \
    git fetch --depth 1 origin "${TULIP_COMMIT}" && \
    git checkout --detach FETCH_HEAD && \
    test "$(git rev-parse HEAD)" = "${TULIP_COMMIT}"

# Build assembler
RUN cp -r /tulip/tulip/services/go-importer /tulip && \
    cd /tulip/go-importer && \
    go build ./cmd/assembler

# Build Tulip PostgreSQL extension from cloned repo
RUN cd /tulip/tulip/services/timescale/tulip && \
    make USE_PGXS=1 install

# Build pg_hint_plan
RUN git init /pg_hint_plan && \
    cd /pg_hint_plan && \
    git remote add origin https://github.com/ossc-db/pg_hint_plan.git && \
    git fetch --depth 1 origin "${PG_HINT_PLAN_COMMIT}" && \
    git checkout --detach FETCH_HEAD && \
    test "$(git rev-parse HEAD)" = "${PG_HINT_PLAN_COMMIT}" && \
    cd /pg_hint_plan && \
    make USE_PGXS=1 install

# copy the schemas
RUN cp -r /tulip/tulip/services/schema /tulip/schema

RUN rm -rf /tulip/tulip && \
    mkdir -p /traffic && \
    chown tcpdump:tcpdump /traffic

COPY requirements.txt /requirements.txt
RUN pip3 install \
    --break-system-packages \
    --no-cache-dir \
    --requirement /requirements.txt

COPY app.py /app.py
COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh
COPY start_capture.sh /start_capture.sh
RUN chmod +x /start_capture.sh

EXPOSE 1337

CMD ["/bin/bash", "/entrypoint.sh"]
