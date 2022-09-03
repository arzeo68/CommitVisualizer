//
// Created by arzeo on 9/3/2022.
//

#include <iostream>
#include <algorithm>
#include "Contributor.hpp"

Contributor::Contributor(Commit commit) {
    this->name = commit.getAuthorName();
    this->addCommit(commit);
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
    for (auto &commit : commits) {
        totalAdditions += commit.getAdditions();
        totalDeletions += commit.getDeletions();
    }

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
