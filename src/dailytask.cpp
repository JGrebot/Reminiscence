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
    m_resultSession["Correct   :"] = 0;
    m_resultSession["Incorrect :"] = 0;
    parse_folder(folderName);
    ask_all_questions();

}


void DailyTask::ask_all_questions(){
    
    int response {0};
    for (auto& [key, vecQuestions] : m_FolderQuestions) {
        for(auto iq = vecQuestions.begin(); iq != vecQuestions.end(); ){
            response = iq->ask_on_terminal(); 
            (response > 0) ? m_resultSession["Correct   :"]++ : m_resultSession["Incorrect :"]++;
            iq = moveQuestion(key, iq, response);
        }
    }
    std::cout << "you have finished !" << std::endl;
    std::cout << "m_resultSession[\"Correct   :\"] = " << m_resultSession["Correct   :"] << std::endl;
    std::cout << "m_resultSession[\"Incorrect :\"] = " << m_resultSession["Incorrect :"] << std::endl;
}


std::vector<Question>::iterator DailyTask::moveQuestion(const int key, std::vector<Question>::iterator iq, int response){

    if(response > 0){
        // Move the corresponding file
        std::filesystem::path current_path = iq->get_path();
        std::filesystem::path new_path = current_path.parent_path() / 
                                         ".." / 
                                         std::to_string(key + 1) / 
                                         current_path.filename();
        std::cout << "current_path = " << current_path << std::endl;
        std::cout << "new_path = " << new_path << std::endl;
        std::filesystem::rename(current_path, new_path);
        iq->set_path(new_path);
        
        // Move the question in the internal map
        iq = m_FolderQuestions[key].erase(iq);
        m_FolderQuestions[key + 1].emplace_back(Question(new_path));

    }else if (key > 1) {
        // Move the corresponding file
        std::filesystem::path current_path = iq->get_path();
        std::filesystem::path new_path = current_path.parent_path() / 
                                         ".." / 
                                         std::to_string(key - 1) / 
                                         current_path.filename();
        std::cout << "current_path = " << current_path << std::endl;
        std::cout << "new_path = " << new_path << std::endl;
        std::filesystem::rename(current_path, new_path);
        iq->set_path(new_path);
        
        // Move the question in the internal map
        iq = m_FolderQuestions[key].erase(iq);
        m_FolderQuestions[key - 1].emplace_back(Question(new_path));
    }else{
        iq ++;
    }
    return iq;
};

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

    // Getting current day as (day_of_year modulo NbChildrenOfprogram_task)
    ryml::ConstNodeRef root = program_task.crootref();
    int program_size = root.num_children();
    int day = day_of_year%program_size;

    // Getting tasks corresponding of day from the program.yaml file
    std::vector<int> folderTasks; 
    ryml::csubstr keys_cday = ryml::to_csubstr("Day" + std::to_string(day));
    int tmp = 0;
    for(ryml::ConstNodeRef n : root[keys_cday].children()){
        n >> tmp;
        folderTasks.emplace_back(tmp);
    }

    // Finally parse all the questions of the required tasks
    for(auto &t : folderTasks){
        for (const auto & question : std::filesystem::directory_iterator(folderName / std::to_string(t))){
            m_FolderQuestions[t].emplace_back( Question(std::filesystem::absolute(question.path())) );
        }
    }

    return 0;
}
