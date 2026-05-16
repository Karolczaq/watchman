//
// Created by Karol Krasoń on 16/05/2026.
//

#ifndef WATCHMAN_SERVICE_H
#define WATCHMAN_SERVICE_H
#include "CheckResult.h"


class Service {
protected:
    std::string name_;
public:
    virtual ~Service() = default;
    virtual Service* clone() const = 0;

    virtual CheckResult check() = 0;

    [[nodiscard]] const std::string& name() const noexcept {return name_;};

    explicit Service(const std::string & name);
};

class HttpService : public Service {
    std::string url_;
public:
    HttpService(std::string name, std::string url);
    CheckResult check() override;
    Service* clone() const override;
};
#endif //WATCHMAN_SERVICE_H