#include <question.hpp>
#include <string>
#include <ryml.hpp>
#include <ryml_std.hpp> 
#include <c4/format.hpp> 
#include <stdlib.h>
#include <filesystem>

#pragma once


class DailyTask{
    public:
    DailyTask();
    ~DailyTask();
    DailyTask(std::string folderName);

    void ask_all_questions();
    void print(int verbose);

    private:
    void get_task_from_program_yaml_file();
    void get_all_questions();

    std::map<int, std::vector<Question> > m_FolderQuestions;
    std::string m_FolderName;
};
