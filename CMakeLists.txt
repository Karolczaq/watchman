cmake_minimum_required(VERSION 3.20)
project(watchman)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL REQUIRED)

add_executable(watchman
        main.cpp
        src/HttpClient.cpp
        include/watchman/HttpClient.h)
target_include_directories(watchman PRIVATE include)
target_link_libraries(watchman PRIVATE CURL::libcurl)
