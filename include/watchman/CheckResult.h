//
// Created by Karol Krasoń on 16/05/2026.
//
#ifndef WATCHMAN_CHECKRESULT_H
#define WATCHMAN_CHECKRESULT_H
#include<string>
struct CheckResult {
    bool up;
    int status;
    std::string detail;
};
#endif //WATCHMAN_CHECKRESULT_H