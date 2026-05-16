#include <iostream>
#include <string>
#include "watchman/ServiceList.h"
#include "watchman/Service.h"

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
        HttpService ser("test",arg);
        CheckResult res = ser.check();
        std::cout << ser.name() << ": "
                    << (res.up ? "UP" : "DOWN")
                    << " (status " << res.status << ")\n";
        ServiceList list;
        list.add(new HttpService("example", "https://example.com"));
        list.add(new HttpService("google", "https://google.com"));

        for (size_t i = 0; i < list.size(); ++i) {
            CheckResult r = list[i]->check();
            std::cout << list[i]->name() << ": " << (r.up ? "UP" : "DOWN") << "\n";
        }
    } catch (const std::exception &e) {
        std::cerr << "błąd! " << e.what() << std::endl;
        return 1;
    }
}
