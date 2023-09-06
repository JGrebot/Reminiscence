#include <question.hpp>
#include <string>
#include <stdlib.h>
#include <filesystem>
#include <ryml.hpp>
#include <ryml_std.hpp> 
#include <c4/format.hpp> 
#include <filesystem>


#pragma once


class DailyTask{
    public:
    DailyTask();
    ~DailyTask(){};
    DailyTask(std::filesystem::path, int);

    void ask_all_questions();
    void reset_all_questions();
    void down_all_questions();
    void print();

    private:
    int parse_folder(std::filesystem::path, int);
    void get_all_questions();
    void parse_program_yaml(std::filesystem::path);
    std::vector<Question>::iterator moveQuestion(const int, std::vector<Question>::iterator, int);

    std::map<int, std::vector<Question>, std::greater<int> > m_FolderQuestions;
    std::map<std::string, int>  m_resultSession;
    std::string m_FolderName;
};
