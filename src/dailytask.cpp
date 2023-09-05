#include <dailytask.hpp>
#include <question.hpp>
#include <string>
#include <ryml.hpp>
#include <ryml_std.hpp> 
#include <c4/format.hpp> 
#include <stdlib.h>
#include <filesystem>
#include <chrono>
#include <ctime>


DailyTask::DailyTask(){
    std::map<int, std::vector<Question> > m_FolderQuestions {};
    std::string m_FolderName {};
}




DailyTask::DailyTask(std::filesystem::path folderName){
    m_FolderName = folderName;

    parse_folder(folderName);
    /* ask_all_question(); */

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
    auto program_task = ryml::parse_in_arena(ryml::to_csubstr(contents)); // immutable (csubstr) overload

    // Get the day of the year (an int between 1 and 365 of the current day)
    int day_of_year = get_day_of_year();
    int day = day_of_year%90;

    std::cout << "What is the current day of the year ?" << std::endl;
    std::cout << "day of year: " << day_of_year << std::endl;
    std::cout << "day : " << day << std::endl;

    // check that the key Day{day_of_year} is defined in the program.yaml file
    // (program_task)

    ryml::ConstNodeRef root = program_task.crootref();

    /* std::string expected_key_string {"Day" + std::to_string(day)}; */
    ryml::csubstr expected_keys = ryml::to_csubstr("Day" + std::to_string(day));
    std::vector<ryml::csubstr> keys, vals; // to store all the root-level keys, vals
    for(ryml::ConstNodeRef n : root.children())
    {
        if (n.key() == expected_keys){
            std::cout << "It's a match !" << std::endl;
            std::cout << "n.key() = " << n.key() << std::endl;
            std::cout << "n.val() = " << n.val() << std::endl;
            break;
        }
    }


    return 0;
}
