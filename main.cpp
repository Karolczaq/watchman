#include <iostream>
#include <string>
#include "watchman/ServiceList.h"
#include "watchman/Service.h"
#include "watchman/Config.h"

constexpr auto VERSION = "1.0";


void print_help() {
    std::cout << "watchman " << VERSION << std::endl;
    std::cout << "uzycie: watchman [opcje]" << std::endl;
    std::cout << "opcje: -h/--help, -v/--version" <<std::endl;
}

int main(const int argc, char* argv[]) {
    if (argc<2) {
        print_help();
        return 1;
    }
    const std::string arg = argv[1];
    if (arg == "-v" || arg =="--version") {
        std::cout<< VERSION << std::endl;
        return 0;
    }
    if (arg == "-h" || arg =="--help") {
        print_help();
        return 0;
    }
    try {
        Config config;
        config.load(arg);

        std::cout<< "watchman " << VERSION << ", loaded " << config.services.size() << " services " << std::endl;

        for (size_t i = 0; i< config.services.size(); i++) {
            Service* s = config.services[i];
            std::cout << " " << s->name() << " (interval " << s->interval() << "s)" << std::endl;
        }


    } catch (const std::exception &e) {
        std::cerr << "błąd! " << e.what() << std::endl;
        return 1;
    }
}
