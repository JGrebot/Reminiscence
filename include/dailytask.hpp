#include <question.hpp>
#include <string>
#include <stdlib.h>
#include <filesystem>
#include <ryml.hpp>
#include <ryml_std.hpp> 
#include <c4/format.hpp> 

#pragma once


class DailyTask{
    public:
    DailyTask();
    ~DailyTask(){};
    DailyTask(std::filesystem::path);

    void ask_all_questions();
    void print(int verbose);

    private:
    int parse_folder(std::filesystem::path);
    void get_all_questions();
    void parse_program_yaml(std::filesystem::path);

    std::map<int, std::vector<Question>, std::greater<int> > m_FolderQuestions;
    std::string m_FolderName;
};
