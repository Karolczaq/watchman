#include "watchman/HttpClient.h"
#include <stdexcept>
//
// Created by Karol Krasoń on 16/05/2026.
//
HttpClient::HttpClient(): handle_(curl_easy_init()) {
    if (!handle_) {
        throw(std::runtime_error("curl_easy_init failed"));
    }
}

HttpClient::~HttpClient() {
    if (handle_) {
        curl_easy_cleanup(handle_);
    }
}

HttpClient::HttpClient(HttpClient &&other) noexcept : handle_(other.handle_){
    other.handle_ = nullptr;
}

HttpClient& HttpClient::operator=(HttpClient &&other) noexcept {
    if (this->handle_ == other.handle_) {
        return *this;
    }
    if (handle_ != nullptr) {
        curl_easy_cleanup(handle_);
    }
    handle_ = other.handle_;
    other.handle_ = nullptr;
    return *this;
}

static size_t discard(char*, size_t size, size_t nmemb, void*) {
    return size * nmemb;
}

int HttpClient::get_status(const std::string &url) {
    curl_easy_setopt(handle_,CURLOPT_URL,url.c_str());
    curl_easy_setopt(handle_, CURLOPT_WRITEFUNCTION, discard);
    curl_easy_setopt(handle_, CURLOPT_TIMEOUT, 5L);
    curl_easy_setopt(handle_, CURLOPT_NOBODY, 1L);
    curl_easy_setopt(handle_, CURLOPT_FOLLOWLOCATION, 1L);

    CURLcode result = curl_easy_perform(handle_);
    if (result != CURLE_OK) {
        throw std::runtime_error(curl_easy_strerror(result));
    }

    long code = 0;
    curl_easy_getinfo(handle_,CURLINFO_HTTP_CODE, &code);
    return static_cast<int>(code);
}

void HttpClient::post(const std::string& url, const std::string& body) {
    curl_easy_setopt(handle_, CURLOPT_URL, url.c_str());
    curl_easy_setopt(handle_, CURLOPT_POSTFIELDS, body.c_str());
    curl_easy_setopt(handle_, CURLOPT_WRITEFUNCTION, discard);
    curl_easy_setopt(handle_, CURLOPT_TIMEOUT, 5L);

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(handle_, CURLOPT_HTTPHEADER, headers);

    CURLcode rc = curl_easy_perform(handle_);
    curl_slist_free_all(headers);

    if (rc != CURLE_OK)
        throw std::runtime_error(curl_easy_strerror(rc));
}
