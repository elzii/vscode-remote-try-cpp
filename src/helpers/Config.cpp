#include <string>
#include <iostream>
// #include <chrono>
#include <time.h>
#include "Config.hpp"
#include <cxxopts.hpp>

/**
 * Define version
 */
#if defined(PROJECT_VERSION)  
const std::string helpers::Config::version = PROJECT_VERSION;
#else
throw new std::exception("The -DPROJECT_VERSION flag was not set.");
#endif

/**
 * Define name
 */
#if defined(PROJECT_NAME)  
const std::string helpers::Config::name = PROJECT_NAME;
#else
throw new std::exception("The -DPROJECT_NAME flag was not set.");
#endif

/**
 * Define description
 */
const std::string helpers::Config::description = "A multi-format data converter (CSV,JSON,TSV)";

/**
 * Define author
 */
const std::string helpers::Config::author = "Alexander Zizzo";

/**
 * Define default options
 */
bool helpers::Config::optDaemon = false;
bool helpers::Config::optDebug = false;

/**
 * Print a banner 
 */
void helpers::Config::printBanner() {
    // std::cout << "██████╗ ██████╗  ██████╗      ██╗███████╗ ██████╗████████╗" << std::endl;
    // std::cout << "██╔══██╗██╔══██╗██╔═══██╗     ██║██╔════╝██╔════╝╚══██╔══╝" << std::endl;
    // std::cout << "██████╔╝██████╔╝██║   ██║     ██║█████╗  ██║        ██║   " << std::endl;
    // std::cout << "██╔═══╝ ██╔══██╗██║   ██║██   ██║██╔══╝  ██║        ██║   " << std::endl;
    // std::cout << "██║     ██║  ██║╚██████╔╝╚█████╔╝███████╗╚██████╗   ██║   " << std::endl;
    // std::cout << "╚═╝     ╚═╝  ╚═╝ ╚═════╝  ╚════╝ ╚══════╝ ╚═════╝   ╚═╝   " << std::endl;
    // const auto now = std::chrono::system_clock::now();
    // const auto year = std::format("{:%Y}", now);
    time_t currTime = time(NULL);
    struct tm *aTime = localtime(&currTime);
    int year = aTime->tm_year + 1900;
    std::cout << "Version " << helpers::Config::version << " - Copyright " << year << " " << helpers::Config::author << std::endl;
    std::cout << std::endl;
}

/**
 * Initialize all arguments
 */
cxxopts::Options helpers::Config::initializeArgs(int argc, char *argv[]) {
    cxxopts::Options options(helpers::Config::name, helpers::Config::description + std::string("\n"));

    options.add_options()
        ("h,help",          "Print this help message and exit.")
        ("d,daemon",        "Launch as a daemon (in the background).")
        ("debug",           "Enable debugging mode.")
    ;

    cxxopts::ParseResult result;

    try {
        result = options.parse(argc, argv);
        // options.parse(argc, argv);
    } catch (const cxxopts::OptionException& e) {
        std::cerr << "Error while parsing options! " << std::endl;
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Show help message if needed
    if (result.count("help")) {
        std::cout << options.help({""}) << std::endl;
        exit(EXIT_SUCCESS);
    }

    // // Set all options
    helpers::Config::optDebug = !!result.count("debug");
    helpers::Config::optDaemon = !!result.count("daemon");

    return options;
}