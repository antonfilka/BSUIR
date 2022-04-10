#ifndef LAB12_9_BRACKETS_CHECK_H
#define LAB12_9_BRACKETS_CHECK_H

#include <iostream>
#include <string>
#include <stack>
#include <fstream>
#include <vector>

class UserException : public std::exception
{
private:
    std::string errorMessage;
public:
    explicit UserException(std::string err_msg) : errorMessage(std::move(err_msg)) {}

    const char *what()
    { return errorMessage.c_str(); }
};

class BracketsCheck
{
private:
    std::string m_sourceFile;
    std::string m_resultFile;

    std::vector<std::string> m_brackets;

    std::vector<std::string> m_correct;
    std::vector<std::string> m_incorrect;
public:
    BracketsCheck(std::string sourceFile, std::string resultFile)
            : m_sourceFile(std::move(sourceFile)), m_resultFile(std::move(resultFile))
    {}

    void loadFromTxt();

    void check();

    void saveInTxt();
};

#endif //LAB12_9_BRACKETS_CHECK_H