#include <iostream>
#include <string>
#include "watchman/ServiceList.h"
#include "watchman/Service.h"
#include "watchman/Config.h"
#include "watchman/Monitor.h"

constexpr auto VERSION = "1.0";


void print_help() {
    std::cout << "\nwatchman " << VERSION << " - monitor usług póki co HTTP \n"<<  std::endl;
    std::cout << "UZYCIE:\n"
          "  watchman <config-path>\n"
          "  watchman -h | --help\n"
          "  watchman -v | --version\n\n"
          "FORMAT CONFIGU (plik .ini):\n"
          "  # linie zaczynajace sie od # to komentarze\n"
          "  <url>  <interwal_w_sekundach>     # usluga do monitorowania\n"
          "  webhook = <url-webhooka-discord>  # opcjonalny webhook\n\n"
          "PRZYKLAD:\n"
          "  https://example.com  5\n"
          "  webhook = https://discord.com/api/webhooks/...\n";
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

        Monitor monitor(config);
        monitor.start();


    } catch (const std::exception &e) {
        std::cerr << "błąd! " << e.what() << std::endl;
        return 1;
    }
}
