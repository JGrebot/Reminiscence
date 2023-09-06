#include <dailytask.hpp>
#include <question.hpp>
#include <ryml.hpp>
#include <ryml_std.hpp> 
#include <c4/format.hpp> 
#include <iostream>
#include <sstream>
#include <vector>
#include <array>
#include <map>
#include <chrono>
#include <ctime>
#include <parser.hpp>

// Command line parser from parser.hpp. See
// ´https://github.com/jermp/cmd_line_parser/tree/master for a full example.
void configure(cmd_line_parser::parser& parser) {
    parser.add("dataFolderPath", 
               "Data folder containing the questions.", 
               "-f", 
               true);
    parser.add("to_reset", 
               "Move all questions to folder 1.", 
               "--reset-DataFolder", 
               false, 
               true);
    parser.add("to_down", 
               "Move each questions down a folder.", 
               "--down-all-questions", 
               false, 
               true);
}



int main(int argc, char** argv) {

    // Parse arguments
    cmd_line_parser::parser parser(argc, argv);
    configure(parser);
    bool success = parser.parse();
    if (!success) return 1;

    auto dataFolderPath = parser.get<std::string>("dataFolderPath");  // deduced type is float
    auto to_reset = parser.get<bool>("to_reset");  // deduced type is float
    auto to_down = parser.get<bool>("to_down");  // deduced type is float
    auto data_folderName = std::filesystem::absolute(std::filesystem::path("/home/fitz/dev/Reminiscence/data"));

    if (to_reset && to_down){
        std::cout << "You cannot both reset and down all questions, you must choose one of the two." << std::endl;
        return 1;
    }
    int reset_down = (to_reset || to_down) ? 1 : 0;

    std::cout << "dataFolderPath: " << dataFolderPath << std::endl;
    std::cout << "to_reset: " << to_reset << std::endl;
    std::cout << "to_down: " << to_down << std::endl;
    std::cout << "data_folderName: " << data_folderName << std::endl;

    DailyTask task { data_folderName, reset_down};

    if(to_reset){
        task.reset_all_questions();
        return 0;
    }
    if(to_down){
        task.down_all_questions();
        return 0;
    }

    task.ask_all_questions();
    return 0;
}


