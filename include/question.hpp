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
    Question(const char *);
     ~Question();

    void print();
    int ask_on_terminal();
    void change_folder(); // TODO

    private:
    void parse_file(const char *); // TODO
    int get_answer_from_user();
    void check_data(); // TODO

    ryml::Tree  m_data;
    std::string m_name;
    int m_folder;

    // Opérateur ?
};


