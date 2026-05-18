FROM debian:bookworm-slim AS build
RUN apt-get update && apt-get install -y \
    cmake g++ libcurl4-openssl-dev && rm -rf /var/lib/apt/lists/*
WORKDIR /app
COPY . .
RUN cmake -S . -B build && cmake --build build
FROM debian:bookworm-slim
RUN apt-get update && apt-get install -y libcurl4 && rm -rf /var/lib/apt/lists/*
COPY --from=build /app/build/watchman /usr/local/bin/watchman
ENTRYPOINT ["watchman", "/config/services.ini"]