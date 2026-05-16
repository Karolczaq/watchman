//
// Created by Karol Krasoń on 16/05/2026.
//

#ifndef WATCHMAN_SERVICELIST_H
#define WATCHMAN_SERVICELIST_H
#include "watchman/Service.h"


class ServiceList {
    Service** data_;
    size_t size_;
    size_t capacity_;
public:
    ServiceList():data_(nullptr),size_(0),capacity_(0){};

    void add(Service* s);
    ~ServiceList();
    size_t size() const {return size_;};

    Service* operator[](size_t i) const{return data_[i];};

    ServiceList(const ServiceList& other);
    ServiceList& operator=(const ServiceList& other);

    ServiceList(ServiceList&& other) noexcept;
    ServiceList& operator=(ServiceList&& other) noexcept ;
};


#endif //WATCHMAN_SERVICELIST_H