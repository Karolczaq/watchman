# watchman
Watchman is a simple HTTP service monitor that can send notifications to discord webhooks.
## Requirements
- C++20 compiler
- CMAKE >= 3.20
- libcurl

## Build
```bash
cmake -S . -B build
cmake --build build
```

## Config
.ini file with one service per line:
```ini
# <url> <interval in seconds>
https://example.com 30
https://kkrason.me 5

# optional discord webhook
webhook = https://discord.com/api/webhooks/...
```
## Usage
```bash
./build/watchman config/services.ini
```

Help: `./build/watchman --help`

## How it works
- each service is pinged once per interval
- service is marked as DOWN if three consecutive pings fail
- service is marked as UP if three consecutive pings are successful
- when the status of service changes a notification is sent
