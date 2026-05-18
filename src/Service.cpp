//
// Created by Karol Krasoń on 16/05/2026.
//

#include "watchman/Service.h"
#include "watchman/HttpClient.h"

HttpService::HttpService(std::string name, std::string url, int interval): Service(name,interval), url_(url){};

CheckResult HttpService::check() {
    try {
        HttpClient client;
        const int status = client.get_status(url_);
        bool up = (status >= 200 && status < 400);
        return CheckResult{up,status,""};
    } catch (const std::exception& e) {
        return CheckResult{false,0,e.what()};
    }
}

Service* HttpService::clone() const {
    return new HttpService(*this);
}

void Service::recordResult(bool up) {
    history_.push(up);
}

bool Service::stableDown() const {
    if (history_.size() < history_.capacity()) {
        return false;
    }
    for (bool up: history_) {
        if (up) {
            return false;
        }
    }
    return true;
}

bool Service::stableUp() const {
    if (history_.size() < history_.capacity()) {
        return false;
    }
    for (bool up: history_) {
        if (!up) {
            return false;
        }
    }
    return true;
}
