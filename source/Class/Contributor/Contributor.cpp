//
// Created by arzeo on 9/3/2022.
//

#include <iostream>
#include <algorithm>
#include <array>
#include <memory>
#include "Contributor.hpp"

Contributor::Contributor(Commit commit) {
    this->name = commit.getAuthorName();
    this->addCommit(commit);
    _repositoryPath = commit.getRepositoryPath();
}

void Contributor::addCommit(Commit commit) {
    this->commits.push_back(commit);
}

int Contributor::getCommitsCount() {
    return this->commits.size();
}

const std::string &Contributor::getName() const {
    return name;
}

void Contributor::dump() {
    std::cout << "Name: " << this->name << std::endl;
    std::cout << "Commits count: " << this->commits.size() << std::endl;


    std::cout << "------------------------" << std::endl;
}

void Contributor::computeAdditionAndDeletion() {

    std::string cmd = "cd " + _repositoryPath + "&& git log --author=\"" + name + "\" --shortstat | awk '/^ [0-9]/ { f += $1; i += $4; d += $6 } END { printf(\"%d files changed, %d insertions(+), %d deletions(-)\", f, i, d) }'";
    std::string res = _executeCommand(cmd.c_str());
    // file changes

    std::string delimiter = " files changed, ";
    size_t pos = res.find(delimiter);
    res.erase(0, pos + delimiter.size());
    totalAdditions = std::atoi(res.c_str());

    delimiter = ", ";
    pos = res.find(delimiter);
    res.erase(0, pos + delimiter.size());
    totalDeletions = std::atoi(res.c_str());
}

void Contributor::_computeAverageCommitPerDay(uint32_t startTimestamp, uint32_t endTimestamp) {
    float diff = endTimestamp - startTimestamp;
    float diffDays = diff / (60 * 60 * 24);

    averageCommitPerDay = (float)(this->commits.size()) / diffDays;
}

size_t Contributor::getTotalAdditions() const {
    return totalAdditions;
}

size_t Contributor::getTotalDeletions() const {
    return totalDeletions;
}

void Contributor::analyse(uint32_t startTimestamp, uint32_t endTimestamp) {
    this->computeAdditionAndDeletion();
    this->_computeAverageCommitPerDay(startTimestamp, endTimestamp);
    this->_computeFirstAndLastCommit();
}

float Contributor::getAverageCommitPerDay() const {
    return averageCommitPerDay;
}

float Contributor::getCodePercentage() const {
    return codePercentage;
}

void Contributor::setCodePercentage(float codePercentage) {
    Contributor::codePercentage = codePercentage;
}

void Contributor::_computeFirstAndLastCommit() {
    std::sort(this->commits.begin(), this->commits.end(), [](const Commit &a, const Commit &b) {
        return a.getTimestamp() < b.getTimestamp();
    });

    this->firstCommitDate = this->commits[0].getDate();
    this->lastCommitDate = this->commits[this->commits.size() - 1].getDate();
}

const std::string &Contributor::getFirstCommitDate() const {
    return firstCommitDate;
}

void Contributor::setFirstCommitDate(const std::string &firstCommitDate) {
    Contributor::firstCommitDate = firstCommitDate;
}

const std::string &Contributor::getLastCommitDate() const {
    return lastCommitDate;
}

void Contributor::setLastCommitDate(const std::string &lastCommitDate) {
    Contributor::lastCommitDate = lastCommitDate;
}

std::string Contributor::_executeCommand(const char *cmd) {
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
