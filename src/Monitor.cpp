//
// Created by Karol Krasoń on 18/05/2026.
//

#include "watchman/Monitor.h"
#include<iostream>

Monitor::Monitor(Config &config): config_(config), notifier_(config.webhook) {
    auto now = std::chrono::steady_clock::now();
    for (std::size_t i = 0;i<config_.services.size();i++) {
        ServiceState state;
        state.nextCheck = now;
        states_.push_back(state);
    }
}

void Monitor::start() {
    while (true) {
        const auto now = std::chrono::steady_clock::now();
        for (size_t i=0 ;i<config_.services.size();i++) {
            if (now >= states_[i].nextCheck) {
                Service* s = config_.services[i];
                ServiceState& state = states_[i];

                auto result = s->check();

                state.nextCheck = now+ std::chrono::seconds(s->interval());

                s->recordResult(result.up);

                if (!state.alerted && s->stableDown()) {
                    std::cout << "DOWN " << s->name() <<std::endl;
                    notifier_.send("🔴 DOWN: " + s->name());
                    state.alerted = true;
                } else if (state.alerted && s->stableUp()) {
                    std::cout << "UP " << s->name() << std::endl;
                    notifier_.send("🟢 UP: " + s->name());
                    state.alerted =false;
                }

            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
