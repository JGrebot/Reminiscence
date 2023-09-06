#include <iostream>
#include <sstream>
#include <vector>
#include <array>
#include <map>
#include <ryml.hpp>
#include <ryml_std.hpp> 
#include <c4/format.hpp> 
#include <filesystem>

#pragma once

class Question {
    public:
    Question();
    Question(std::filesystem::path);
     ~Question();

    void print() const;
    int ask_on_terminal() const;

    std::filesystem::path get_path();
    void set_path(std::filesystem::path);

    private:
    void parse_file(std::filesystem::path); // TODO
    int get_answer_from_user() const;
    void check_data(); // TODO

    ryml::Tree  m_data;
    std::filesystem::path m_name;
    int m_folder;

    // Opérateur ?
};


// helper functions for sample_parse_file()
template<class CharContainer> CharContainer file_get_contents(const char *filename);
template<class CharContainer> size_t        file_get_contents(const char *filename, CharContainer *v);
template<class CharContainer> void          file_put_contents(const char *filename, CharContainer const& v, const char* access="wb");
void                                        file_put_contents(const char *filename, const char *buf, size_t sz, const char* access);


