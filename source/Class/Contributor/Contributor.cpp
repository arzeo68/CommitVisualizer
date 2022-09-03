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
