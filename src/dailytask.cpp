#include <dailytask.hpp>
#include <question.hpp>
#include <string>
#include <stdlib.h>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <ryml.hpp>
#include <ryml_std.hpp> 
#include <c4/format.hpp> 


DailyTask::DailyTask(){
    std::map<int, std::vector<Question> > m_FolderQuestions {};
    std::string m_FolderName {};
}




DailyTask::DailyTask(std::filesystem::path folderName){
    m_FolderName = folderName;

    parse_folder(folderName);
    ask_all_questions();

}


void DailyTask::ask_all_questions(){
    
    int response_false {0};
    int response_true {0};
    for (const auto& [key, vecQuestions] : m_FolderQuestions) {
        for(auto iq = vecQuestions.begin(); iq != vecQuestions.end(); iq ++){
            (iq->ask_on_terminal() > 0) ? response_true++ : response_false++;
        }
    }
    std::cout << "you have finished !" << std::endl;
    std::cout << "response_true = " << response_true << std::endl;
    std::cout << "response_false = " << response_false << std::endl;
}

/**
 * Compute the number (over 365) of the current day.
 *
 */
int get_day_of_year(){

    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    struct tm *parts = std::localtime(&now_c);

    int year    {1900 + parts->tm_year}; 
    int month   {parts->tm_mon}; // starts at 0
    int day     {parts->tm_mday}; // starts at 1

    // days of all 12 months.
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // If current year is a leap year and the date
    // given is after the 28th of February then
    // it must include the 29th February
    if (month > 2 && year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
        ++day;
    }

    // Add the days of the previous months
    for (int m = 0; m<month; m++){
        day += days[m];
    }
    return day;
}


int DailyTask::parse_folder(std::filesystem::path folderName){

    auto program_yaml_path = folderName / "program.yaml";

    if (! std::filesystem::exists(folderName)){
        std::cout << "The folder " << folderName << " does not exist." << std::endl;
        return 1;
    }
    if (! std::filesystem::exists(program_yaml_path)){
        std::cout << "No program.yaml file found in the folder " << folderName << std::endl;
        return 1;
    }

    // Parse the folderName/program.yaml file
    std::string contents = file_get_contents<std::string>(program_yaml_path.c_str());
    auto program_task = ryml::parse_in_arena(ryml::to_csubstr(contents)); 

    // Get the day of the year (an int between 1 and 365 of the current day)
    int day_of_year = get_day_of_year();

    /* std::cout << "What is the current day of the year ?" << std::endl; */
    /* std::cout << "day of year: " << day_of_year << std::endl; */

    // Getting current day as (day_of_year modulo NbChildrenOfprogram_task)
    ryml::ConstNodeRef root = program_task.crootref();
    int program_size = root.num_children();
    int day = day_of_year%program_size;
    
    /* std::cout << "program_size : " << program_size << std::endl; */
    /* std::cout << "day : " << day << std::endl; */

    // Getting tasks corresponding of day from the program.yaml file
    std::vector<int> folderTasks; 
    ryml::csubstr keys_cday = ryml::to_csubstr("Day" + std::to_string(day));
    int tmp = 0;
    for(ryml::ConstNodeRef n : root[keys_cday].children()){
        n >> tmp;
        folderTasks.emplace_back(tmp);
    }

    /* std::cout << "keys_cday = " << keys_cday << std::endl; */
    /* for(auto n : folderTasks){ */
    /*     std::cout << n << std::endl; */
    /* } */

    // Finally parse all the questions of the required tasks
    for(auto &t : folderTasks){
        for (const auto & question : std::filesystem::directory_iterator(folderName / std::to_string(t))){
            m_FolderQuestions[t].emplace_back( Question(question.path().string()) );
            /* std::cout << question.path() << std::endl; */
        }
    }

    /* m_FolderQuestions[1][0].print(); */
    /* m_FolderQuestions[1][1].print(); */
    /* m_FolderQuestions[1][2].print(); */

    return 0;
}
