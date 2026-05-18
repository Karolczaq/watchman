//
// Created by Karol Krasoń on 18/05/2026.
//

#include "../include/watchman/Config.h"
#include "watchman/util.h"
#include "watchman/Service.h"
#include <fstream>
#include <stdexcept>

void Config::load(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Can't open file" + path);
    }

    std::string line;
    while (std::getline(file,line)) {
        std::vector<std::string> tokens = split(line);

        if (tokens.empty()) {
            continue;
        }
        if (tokens[0][0] == '#') {
            continue;
        }
        if (tokens.size() == 3 && tokens[0] == "webhook" && tokens[1] == "=") {
            webhook = tokens[2];
        }
        else if (tokens.size() == 2) {
            services.add(new HttpService(tokens[0],tokens[0],std::stoi(tokens[1])));
        }
    }
}