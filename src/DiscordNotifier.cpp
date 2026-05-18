//
// Created by Karol Krasoń on 18/05/2026.
//

#include "watchman/DiscordNotifier.h"
#include <iostream>

DiscordNotifier::DiscordNotifier(const std::string& webhook):webhook_(webhook) {}

void DiscordNotifier::send(const std::string& message) {
    if (webhook_.empty()) {
        return;
    }
    std::string json = "{\"content\":\"" + message + "\"}";
    try {
        client_.post(webhook_, json);
    }catch (std::exception &e) {
        std::cerr << "Couldn't send the message" << e.what() << std::endl;
    }
}
