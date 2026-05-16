#include <iostream>
#include <string>
#include "watchman/HttpClient.h"

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
        HttpClient client;
        int status = client.get_status(arg);
        std::cout << "sprawdzam: " << arg << std::endl;
        std::cout << "status: " << status << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "błąd! " << e.what() << std::endl;
        return 1;
    }
}
