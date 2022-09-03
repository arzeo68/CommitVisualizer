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

    float getCodePercentage() const;

    void setCodePercentage(float codePercentage);

private:

    void _computeAverageCommitPerDay(uint32_t startTimestamp, uint32_t endTimestamp);
    void computeAdditionAndDeletion();
    void _computeFirstAndLastCommit();

public:
    const std::string &getFirstCommitDate() const;

    void setFirstCommitDate(const std::string &firstCommitDate);

    const std::string &getLastCommitDate() const;

    void setLastCommitDate(const std::string &lastCommitDate);

private:
    std::string _executeCommand(const char* cmd);
    float codePercentage = 0;
    std::string name;
    std::vector<Commit> commits;
    size_t totalAdditions = 0;
    size_t totalDeletions = 0;
    std::string firstCommitDate;
    std::string lastCommitDate;
    float averageCommitPerDay = 0;

    std::string _repositoryPath;
};


#endif //REPOSITORYSTAT_CONTRIBUTOR_HPP
