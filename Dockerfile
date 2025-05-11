
FROM ubuntu:20.04 AS builder

WORKDIR /app

RUN apt-get update && apt-get install -y --no-install-recommends \
    gcc \
    make \
    pkg-config \
    libsqlite3-dev \
    libgtk-3-dev && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

COPY . .

RUN make && chmod +x /app/bin/DevAuth

FROM ubuntu:20.04

RUN apt-get update && apt-get install -y --no-install-recommends \
    libsqlite3-0 \
    libgtk-3-0 && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

COPY --from=builder /app/bin/DevAuth /usr/local/bin/DevAuth

ENTRYPOINT ["/usr/local/bin/DevAuth"]