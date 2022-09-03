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
#include <sstream>
#include <algorithm>
#include "CommitsHandler.hpp"
#include "../../prettyPrinter.hpp"
#include "../../utils.hpp"

std::string CommitsHandler::_executeCommand(const char *cmd) {
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

CommitsHandler::CommitsHandler(std::string path): _repositoryPath(path) {
    std::string command = "cd " + _repositoryPath + " && git log --pretty=format:\"%H%x09%an%x09%as%x09%at%x09%s\"";
    _log =  _executeCommand(command.c_str());
    getBranches(_repositoryPath);
    splitLogIntoCommit(_log);
    splitCommitIntoAuthors();
    _display();
}

void CommitsHandler::splitLogIntoCommit(std::string log) {
    std::string delimiter = "\n";
    std::vector<std::string> commits;

    size_t pos = 0;
    std::string token;
    while ((pos = log.find(delimiter)) != std::string::npos) {
        token = log.substr(0, pos);
        commits.emplace_back(token);
        log.erase(0, pos + delimiter.length());
    }
    commits.emplace_back(log);

    for (auto &commit : commits) {
        _commits.emplace_back(Commit(commit, _repositoryPath));
    }

}

void CommitsHandler::splitCommitIntoAuthors() {
    for (auto &commit: _commits) {
        if (_contributors.find(commit.getAuthorName()) == _contributors.end()) {
            _contributors.insert(std::pair<std::string, Contributor>(commit.getAuthorName(), Contributor(commit)));
        } else {
            _contributors.at(commit.getAuthorName()).addCommit(commit);
        }
    }

}

void CommitsHandler::_display() {
    std::pair<Commit, Commit> startAndEndCommit = getStartAndEndCommit();
    VariadicTable<int, int, int ,std::string, std::string> vtRepo({"Commits count", "Branches count", "Contributors count", "First commit", "Last commit"}, 15);
    vtRepo.addRow(_commits.size(), _branches.size(), _contributors.size(), startAndEndCommit.first.getDate(), startAndEndCommit.second.getDate());
    vtRepo.print(std::cout);
    VariadicTable<std::string, int, double, int ,int, std::string, std::string> vtUser({"Name", "Commits", "Commit %", "Additions(+)", "Deletions(-)", "First commit", "Last commit"}, 15);
    vtUser.setColumnPrecision({1, 1, 2, 1, 1, 1,1});
    vtUser.setColumnFormat({VariadicTableColumnFormat::AUTO,
                        VariadicTableColumnFormat::AUTO,
                        VariadicTableColumnFormat::PERCENT,
                        VariadicTableColumnFormat::AUTO,
                        VariadicTableColumnFormat::AUTO,
                        VariadicTableColumnFormat::AUTO,VariadicTableColumnFormat::AUTO});

    float totalCode = 0;
    for (auto &contributor : _contributors) {
        contributor.second.analyse(startAndEndCommit.first.getTimestamp(), startAndEndCommit.second.getTimestamp());
        totalCode += contributor.second.getTotalAdditions() - contributor.second.getTotalDeletions();
    }

    std::vector<Contributor> contribVector;
    for( auto it = _contributors.begin(); it != _contributors.end(); ++it ) {
        contribVector.push_back( it->second );
    }
    std::sort(contribVector.begin(), contribVector.end(), [this](Contributor a, Contributor b) {
        float commitPercentageA = (float)(a.getCommitsCount()) / (float)(_commits.size()) * 100;
        float commitPercentageB = (float)(b.getCommitsCount()) / (float)(_commits.size()) * 100;

        return commitPercentageA > commitPercentageB;
    });

    for (auto contrib: contribVector) {
        float commitPercentage = (float)(contrib.getCommitsCount()) / (float)(_commits.size()) * 100;
        vtUser.addRow(contrib.getName(), contrib.getCommitsCount(), commitPercentage, contrib.getTotalAdditions(), contrib.getTotalDeletions(), contrib.getFirstCommitDate(), contrib.getLastCommitDate());
    }
    vtUser.print(std::cout);
}

void CommitsHandler::getBranches(std::string path) {
    std::string command = "cd " + path + " && git branch -a";
    std::string res = _executeCommand(command.c_str());
    std::string line;
    std::istringstream iss(res);
    while (std::getline(iss, line)) {
       _branches.emplace_back(line);
    }
    return;
}

std::pair<Commit, Commit> CommitsHandler::getStartAndEndCommit() {
    std::vector<Commit> tmp = _commits;
    std::sort(tmp.begin(), tmp.end(), [](const Commit &a, const Commit &b) {
        return a.getTimestamp() < b.getTimestamp();
    });
    return std::pair<Commit, Commit>(tmp.front(), tmp.back());
}
