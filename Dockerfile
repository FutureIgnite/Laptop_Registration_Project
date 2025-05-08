FROM ubuntu:20.04 AS builder

WORKDIR /app

RUN apt-get update && apt-get install -y --no-install-recommends \
    gcc \
    cmake \
    libsqlite3-dev \
    libncurses5-dev \
    make && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

COPY . .

RUN make && chmod +x /app/bin/DevAuth

# -- Final stage --
FROM alpine

# Install glibc compatibility layer (Alpine uses musl by default)
RUN apk add --no-cache libc6-compat

COPY --from=builder /app/bin/DevAuth /usr/local/bin/DevAuth

ENTRYPOINT ["/usr/local/bin/DevAuth"]
