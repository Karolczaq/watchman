//
// Created by Karol Krasoń on 18/05/2026.
//

#ifndef WATCHMAN_DISCORDNOTIFIER_H
#define WATCHMAN_DISCORDNOTIFIER_H
#include "HttpClient.h"


class DiscordNotifier {
    std::string webhook_;
    HttpClient client_;
public:
    DiscordNotifier(const std::string& webhook);
    void send(const std::string& message);
};


#endif //WATCHMAN_DISCORDNOTIFIER_H