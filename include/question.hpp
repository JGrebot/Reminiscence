#include <ryml.hpp>
#include <ryml_std.hpp> 
#include <c4/format.hpp> 
#include <iostream>
#include <sstream>
#include <vector>
#include <array>
#include <map>

#pragma once

class Question {
    public:
    Question();
    Question(std::string);
     ~Question();

    void print();
    int ask_on_terminal();

    private:
    void parse_file(std::string); // TODO
    int get_answer_from_user();
    void check_data(); // TODO

    ryml::Tree  m_data;
    std::string m_name;
    int m_folder;

    // Opérateur ?
};


