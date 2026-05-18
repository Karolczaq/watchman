//
// Created by Karol Krasoń on 18/05/2026.
//

#ifndef WATCHMAN_MONITOR_H
#define WATCHMAN_MONITOR_H
#include <chrono>
#include <vector>
#include <thread>
#include "Config.h"
#include "DiscordNotifier.h"

struct ServiceState {
    std::chrono::steady_clock::time_point nextCheck;
    bool alerted = false;
};

class Monitor {
    Config& config_;
    DiscordNotifier notifier_;
    std::vector<ServiceState> states_;
public:
    Monitor(Config& config);

    void start();

};

#endif //WATCHMAN_MONITOR_H

