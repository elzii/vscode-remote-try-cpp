#include <cstdlib>
#include <poll.h>
#include <string>
#include <iostream>
#include <toml/tinytoml.h>
#include <cxxopts.hpp>
#include "lib/json.h"
#include "helpers/Config.hpp"

// https://github.com/sheredom/json.h
// https://github.com/nlohmann/json
// https://fmt.dev/latest/index.html
// https://github.com/jbeder/yaml-cpp/tree/master/include/yaml-cpp
// https://github.com/mayah/tinytoml/blob/master/src/parser_test.cc


    
using namespace std;

int main(int argc, char *argv[]) {
    helpers::Config::printBanner();
    helpers::Config::initializeArgs(argc, argv);
    
    // std::string iv;
    // getline(std::cin, iv);   
    // bool has_stdin = !iv.empty();

    // int has_stdin;
    // std::cin >> has_stdin;

    pollfd fd = {
        fd: 0,
        events: POLLIN
    };

    if (poll(&fd, 1, 0) == 1) {
        // std::cout << "HAS STDIN" << std::endl;
        toml::ParseResult res = toml::parse(std::cin);
        if ( res.valid() ) {
            // size_t index = 0;
            // auto val = res.value.find(index);
            auto val = res.value.get<string>("owner.name");
            std::cout << val << std::endl;
            // std::cout << res.value << std::endl;
        } else {
            std::cout << "Invalid TOML File" << std::endl;
            std::cout << res.errorReason << std::endl;
        }

    } else {
        // std::cout << "NO STDIN" << std::endl;
        
        const char json[] = "{\"a\": true}";
        struct json_value_s* root = json_parse(json, strlen(json));

        std::cout << "JSON PARSE: " << root << std::endl;
        
    }

       




    return EXIT_SUCCESS;

    // const char *tomlStr = 
    // "thing: true" 
    // "name: 'Alexander'";
}