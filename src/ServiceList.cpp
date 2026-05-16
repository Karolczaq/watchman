//
// Created by Karol Krasoń on 16/05/2026.
//

#include "watchman/ServiceList.h"

void ServiceList::add(Service *s) {
    if (size_ == capacity_) {
        capacity_ = capacity_ == 0 ? 4 : capacity_*2;
        Service** newdata = new Service*[capacity_];
        for (size_t i=0;i<size_;i++) {
            newdata[i] = data_[i];
        }
        delete[] data_;
        data_ = newdata;
    }
    data_[size_] = s;
    size_++;
}

ServiceList::~ServiceList() {
    for (size_t i= 0; i<size_;i++) {
        delete data_[i];
    }
    delete[] data_;
}

ServiceList::ServiceList(const ServiceList &other) {
    data_ = new Service*[other.capacity_];
    size_ = other.size_;
    capacity_ = other.capacity_;
    for (size_t i = 0; i<other.size_; i++) {
        data_[i] = other.data_[i]->clone();
    }
}

ServiceList& ServiceList::operator=(const ServiceList &other) {
    if (this == &other) {
        return *this;
    }
    for (size_t i =0;i<size_;i++) {
        delete data_[i];
    }
    delete[] data_;
    data_ = new Service*[other.capacity_];
    for (size_t i =0;i<other.size_;i++) {
        data_[i] = other.data_[i]->clone();
    }
    size_ = other.size_;
    capacity_ = other.capacity_;
    return *this;
}

ServiceList::ServiceList(ServiceList &&other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_){
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

ServiceList& ServiceList::operator=(ServiceList&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    for (size_t i =0;i<size_;i++) {
        delete data_[i];
    }
    delete[] data_;
    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
    return *this;
}

