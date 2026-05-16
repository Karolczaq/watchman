//
// Created by Karol Krasoń on 16/05/2026.
//

#ifndef WATCHMAN_HTTPCLIENT_H
#define WATCHMAN_HTTPCLIENT_H

#include <string>
#include <curl/curl.h>
class HttpClient {
    CURL* handle_;

public:
    HttpClient();
    ~HttpClient();

    HttpClient(const HttpClient &other) = delete;
    HttpClient& operator=(const HttpClient &other) = delete;

    HttpClient(HttpClient &&other) noexcept;
    HttpClient& operator=(HttpClient &&other) noexcept;

    int get_status(const std::string &url);
};

#endif //WATCHMAN_HTTPCLIENT_H
