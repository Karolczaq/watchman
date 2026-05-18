//
// Created by Karol Krasoń on 18/05/2026.
//

#ifndef WATCHMAN_CONFIG_H
#define WATCHMAN_CONFIG_H
#include <string>
#include "watchman/ServiceList.h"


class Config {
public:
    ServiceList services;
    std::string webhook;

    void load (const std::string& path);
};


#endif //WATCHMAN_CONFIG_H