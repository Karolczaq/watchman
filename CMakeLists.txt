cmake_minimum_required(VERSION 3.20)
project(watchman)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL REQUIRED)

add_executable(watchman
        main.cpp
        src/HttpClient.cpp
        src/Service.cpp
        src/ServiceList.cpp
        src/util.cpp
        src/Config.cpp
        src/Monitor.cpp
        include/watchman/HttpClient.h
        include/watchman/Service.h
        include/watchman/CheckResult.h
        include/watchman/ServiceList.h
        include/watchman/RingBuffer.h
        include/watchman/util.h
        include/watchman/Config.h
        include/watchman/Monitor.h)
target_include_directories(watchman PRIVATE include)
target_link_libraries(watchman PRIVATE CURL::libcurl)
