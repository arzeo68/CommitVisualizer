//
// Created by arzeo on 9/3/2022.
//

#include <iostream>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <fstream>
#include "Class/CommitHandler/CommitsHandler.hpp"

std::string executeCommand(const char *cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

void printHelp() {
    std::cout << "Usage:" << std::endl;
    std::cout << "\trepositoryStat <path to git repository>" << std::endl;
    std::cout << "\trepositoryStat -c --clone <git repository url>" << std::endl;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "Please provide a path to a git repository" << std::endl;
        return 1;
    }
    if (argc > 3) {
        std::cout << "Too many arguments" << std::endl;
        return 1;
    }
    if (argc == 2) {
        if (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h") {
            printHelp();
            return 0;
        }
        CommitsHandler commitsHandler(argv[1]);
    }

    if (argc == 3) {
        if (std::string(argv[1]) != "-c" && std::string(argv[1]) != "--clone") {
            printHelp();
            return 0;
        }

        executeCommand("rm -rf tmpRepositoryStat");
        std::string res = executeCommand(("git clone " + std::string(argv[2]) + " tmpRepositoryStat").c_str());
        CommitsHandler commitsHandler("./tmpRepositoryStat");
        executeCommand("rm -rf tmpRepositoryStat");
    }


    return 0;
}