//
// Created by arzeo on 9/3/2022.
//

#ifndef COMMITVIRTULAIZER_COMMIT_HPP
#define COMMITVIRTULAIZER_COMMIT_HPP


#include <string>

class Commit {
    public:
    Commit(std::string commit, std::string path);

    const std::string &getCommit() const;

    const std::string &getHash() const;

    const std::string &getMessage() const;

    const std::string &getAuthorName() const;

    const std::string &getDate() const;

    bool isMerge() const;

    uint32_t getTimestamp() const;

private:

    void _dump();
    void parse();
    void _computeAdditionAndDeletion();
    std::string _commit;
    std::string hash;
    std::string message;
    std::string authorName;
public:
    uint32_t getAdditions() const;

    uint32_t getDeletions() const;

private:

    std::string _executeCommand(const char* cmd);
    std::string date;
    uint32_t timestamp;
    uint32_t additions = 0;
    uint32_t deletions = 0;

    std::string _repositoryPath;
    bool _isMerge = false;
};


#endif //COMMITVIRTULAIZER_COMMIT_HPP
