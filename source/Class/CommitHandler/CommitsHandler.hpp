//
// Created by arzeo on 9/3/2022.
//

#ifndef COMMITVIRTULAIZER_COMMITSHANDLER_HPP
#define COMMITVIRTULAIZER_COMMITSHANDLER_HPP


#include <vector>
#include <map>
#include "../Commit/Commit.hpp"
#include "../Contributor/Contributor.hpp"

class CommitsHandler {
public:
    CommitsHandler(std::string path);
private:
    void getBranches(std::string path);
    void splitLogIntoCommit(std::string log);
    void splitCommitIntoAuthors();
    std::pair<Commit, Commit> getStartAndEndCommit();

    void _display();
    std::vector<Commit> _commits;
    std::string _log;
    std::vector<std::string> _branches;
    std::map<std::string, Contributor> _contributors;
    std::string _repositoryPath;
    std::string _executeCommand(const char* cmd);
};


#endif //COMMITVIRTULAIZER_COMMITSHANDLER_HPP
