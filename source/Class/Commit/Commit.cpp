//
// Created by arzeo on 9/3/2022.
//

#include <iostream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <time.h>
#include "Commit.hpp"
#include "../../utils.hpp"

Commit::Commit(std::string commit, std::string path): _commit(commit), _repositoryPath(path) {
    parse();
}

void Commit::parse() {
    std::string cpy = _commit;

    // hash
    size_t pos = cpy.find("\t");
    hash = cpy.substr(0, pos);
    cpy.erase(0, pos + 1);

    // author
    pos = cpy.find("\t");
    authorName = cpy.substr(0, pos);
    cpy.erase(0, pos + 1);

    // date
    pos = cpy.find("\t");
    date = cpy.substr(0, pos);
    cpy.erase(0, pos + 1);

    // date
    pos = cpy.find("\t");
    timestamp = std::atoi(cpy.substr(0, pos).c_str());
    cpy.erase(0, pos + 1);

    // message
    message = cpy;

//    _dump();
    _computeAdditionAndDeletion();
}

void Commit::_dump() {
    std::cout << "---------------------" << std::endl;
    std::cout << "Parsing commit: " << this->_commit << std::endl;
    std::cout << "hash: " << hash << std::endl;
    std::cout << "message: " << message << std::endl;
    std::cout << "author name: " << authorName << std::endl;
    std::cout << "date: " << date << std::endl;
    std::cout << "timestamp: " << timestamp << std::endl;
    std::string isMergeText = _isMerge ? "True" : "False";
    std::cout << "isMerge: " << isMergeText << std::endl;
    std::cout << "---------------------" << std::endl;
}

const std::string &Commit::getCommit() const {
    return _commit;
}

const std::string &Commit::getHash() const {
    return hash;
}

const std::string &Commit::getMessage() const {
    return message;
}

const std::string &Commit::getAuthorName() const {
    return authorName;
}

const std::string &Commit::getDate() const {
    return date;
}

bool Commit::isMerge() const {
    return _isMerge;
}

uint32_t Commit::getTimestamp() const {
    return timestamp;
}

void Commit::_computeAdditionAndDeletion() {
    std::string command = "cd " + _repositoryPath + " && git diff --shortstat " + hash +"~ " + hash;
    std::string res = _executeCommand(command.c_str());

    std::string delimiter = ", ";
    std::vector<std::string> stats;

    size_t pos = 0;
    std::string token;

    while ((pos = res.find(delimiter)) != std::string::npos) {
        token = res.substr(0, pos);
        stats.emplace_back(token);
        res.erase(0, pos + delimiter.length());
    }
    stats.emplace_back(res);

    for (auto &stat : stats) {
        if ((pos = stat.find("insertions(+)")) != std::string::npos) {
            additions += std::atoi(stat.substr(0, pos - 1).c_str());
//
        } else if ((pos = stat.find("deletions(-)")) != std::string::npos) {
            deletions += std::atoi(stat.substr(0, pos - 1).c_str());
        }
    }
}

uint32_t Commit::getAdditions() const {
    return additions;
}

uint32_t Commit::getDeletions() const {
    return deletions;
}

std::string Commit::_executeCommand(const char *cmd) {
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
