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
#include "Class/CommitHandler/CommitsHandler.hpp"



int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "Please provide a path to a git repository" << std::endl;
        return 1;
    }
    if (argc > 2) {
        std::cout << "Too many arguments" << std::endl;
        return 1;
    }
    if (argc == 2) {
        if (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h") {
            std::cout << "Usage: repositoryStat <path to git repository>" << std::endl;
            return 0;
        }
        CommitsHandler commitsHandler(argv[1]);
    }
    return 0;
}