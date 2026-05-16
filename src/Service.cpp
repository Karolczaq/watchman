//
// Created by Karol Krasoń on 16/05/2026.
//

#include "watchman/Service.h"
#include "watchman/HttpClient.h"

HttpService::HttpService(std::string name, std::string url): Service(name), url_(url){};

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

Service::Service(const std::string &name):name_(name) {}

Service* HttpService::clone() const {
    return new HttpService(*this);
}
