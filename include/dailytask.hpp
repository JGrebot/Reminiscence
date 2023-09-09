#pragma once
#include "c4/yml/node.hpp"
#include <question.hpp>
#include <string>
#include <stdlib.h>
#include <filesystem>
#include <ryml.hpp>
#include <ryml_std.hpp> 
#include <c4/format.hpp> 
#include <filesystem>




class DailyTask{
    public:
    DailyTask();
    ~DailyTask(){};
    DailyTask(std::filesystem::path, int);

    void ask_all_questions();
    void reset_all_questions();
    void down_all_questions();
    void check_Folders(std::filesystem::path, int);
    int get_Max_TaskFolder(ryml::ConstNodeRef);
    std::string get_folderName();
    int get_good_answer();
    int get_wrong_answer();
    int get_programDay();
    std::map<int, std::vector<Question>, std::greater<int> > get_folderQuestion();
    void print();

    private:
    int parse_folder(std::filesystem::path, int);
    void get_all_questions();
    void parse_program_yaml(std::filesystem::path);
    std::vector<Question>::iterator moveQuestion(const int, std::vector<Question>::iterator, int);

    std::map<int, std::vector<Question>, std::greater<int> > m_FolderQuestions;
    std::map<std::string, int>  m_resultSession;
    std::string m_FolderName;
    int m_programDay;
};
