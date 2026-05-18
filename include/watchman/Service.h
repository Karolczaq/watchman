//
// Created by Karol Krasoń on 16/05/2026.
//

#ifndef WATCHMAN_SERVICE_H
#define WATCHMAN_SERVICE_H
#include "CheckResult.h"
#include "watchman/RingBuffer.h"


class Service {
protected:
    std::string name_;
    RingBuffer<bool> history_;
    int interval_;
public:
    virtual ~Service() = default;
    virtual Service* clone() const = 0;

    virtual CheckResult check() = 0;

    [[nodiscard]] const std::string& name() const noexcept {return name_;};

    Service(const std::string & name, const int& interval): name_(name), interval_(interval), history_(3){};

    void recordResult(bool up);
    [[nodiscard]] bool stableDown() const;
    [[nodiscard]] bool stableUp() const;

    [[nodiscard]] int interval() const{return interval_;};
};

class HttpService : public Service {
    std::string url_;
public:
    HttpService(std::string name, std::string url, int interval);
    CheckResult check() override;
    Service* clone() const override;
};
#endif //WATCHMAN_SERVICE_H