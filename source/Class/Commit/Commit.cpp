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

uint32_t Commit::getAdditions() const {
    return additions;
}

uint32_t Commit::getDeletions() const {
    return deletions;
}
const std::string &Commit::getRepositoryPath() const {
    return _repositoryPath;
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
