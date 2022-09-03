//
// Created by arzeo on 9/3/2022.
//

#ifndef REPOSITORYSTAT_CONTRIBUTOR_HPP
#define REPOSITORYSTAT_CONTRIBUTOR_HPP


#include <vector>
#include "../Commit/Commit.hpp"

class Contributor {
public:
    Contributor(Commit commit);
    void addCommit(Commit commit);
    int getCommitsCount();
    void analyse(uint32_t startTimestamp, uint32_t endTimestamp);

    size_t getTotalAdditions() const;

    size_t getTotalDeletions() const;

    void dump();

    const std::string &getName() const;
    float getAverageCommitPerDay() const;

private:

    void _computeAverageCommitPerDay(uint32_t startTimestamp, uint32_t endTimestamp);
    void computeAdditionAndDeletion();

    float codePercentage = 0;
public:
    float getCodePercentage() const;

    void setCodePercentage(float codePercentage);

private:
    std::string name;
    std::vector<Commit> commits;
    size_t totalAdditions = 0;
    size_t totalDeletions = 0;
    float averageCommitPerDay = 0;
};


#endif //REPOSITORYSTAT_CONTRIBUTOR_HPP
