#include <vector>
#include <string>
#include <sstream>
#include "watchman/util.h"
//
// Created by Karol Krasoń on 18/05/2026.
//
std::vector<std::string> split(const std::string& input) {
    std::vector<std::string> result;
    std::istringstream stream(input);
    std::string word;
    while (stream >> word) {
        result.push_back(word);
    }
    return result;
}