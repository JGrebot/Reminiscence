#include <dailytask.hpp>
#include <question.hpp>
#include <string>
#include <ryml.hpp>
#include <ryml_std.hpp> 
#include <c4/format.hpp> 
#include <stdlib.h>
#include <filesystem>


DailyTask::DailyTask(){
    std::map<int, std::vector<Question> > m_FolderQuestions {};
    std::string m_FolderName {};
}




DailyTask::DailyTask(std::string folderName){
    m_FolderName = folderName;

    // find the program.yaml name.
    // raise an exception if several are found.

    // append the program file name

    this->get_task_from_program_yaml_file();
}


void DailyTask::get_task_from_program_yaml_file(){
    std::cout << "loading the program yaml file " << std::endl;
}
