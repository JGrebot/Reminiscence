#include <tmp.hpp>
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




/*// helper functions for sample_parse_file() */
/*template<class CharContainer> CharContainer file_get_contents(const char *filename); */
/*template<class CharContainer> size_t        file_get_contents(const char *filename, CharContainer *v); */
/*template<class CharContainer> void          file_put_contents(const char *filename, CharContainer const& v, const char* access="wb"); */
/*void                                        file_put_contents(const char *filename, const char *buf, size_t sz, const char* access); */

/*C4_SUPPRESS_WARNING_MSVC_WITH_PUSH(4996) // fopen: this function or variable may be unsafe */
/*/1** load a file from disk and return a newly created CharContainer *1/ */
/*template<class CharContainer> */
/*size_t file_get_contents(const char *filename, CharContainer *v) */
/*{ */
/*    ::FILE *fp = ::fopen(filename, "rb"); */
/*    C4_CHECK_MSG(fp != nullptr, "could not open file"); */
/*    ::fseek(fp, 0, SEEK_END); */
/*    long sz = ::ftell(fp); */
/*    v->resize(static_cast<typename CharContainer::size_type>(sz)); */
/*    if(sz) */
/*    { */
/*        ::rewind(fp); */
/*        size_t ret = ::fread(&(*v)[0], 1, v->size(), fp); */
/*        C4_CHECK(ret == (size_t)sz); */
/*    } */
/*    ::fclose(fp); */
/*    return v->size(); */
/*} */

/*/1** load a file from disk into an existing CharContainer *1/ */
/*template<class CharContainer> */
/*CharContainer file_get_contents(const char *filename) */
/*{ */
/*    CharContainer cc; */
/*    file_get_contents(filename, &cc); */
/*    return cc; */
/*} */

/*/1** save a buffer into a file *1/ */
/*template<class CharContainer> */
/*void file_put_contents(const char *filename, CharContainer const& v, const char* access) */
/*{ */
/*    file_put_contents(filename, v.empty() ? "" : &v[0], v.size(), access); */
/*} */

/*/1** save a buffer into a file *1/ */
/*void file_put_contents(const char *filename, const char *buf, size_t sz, const char* access) */
/*{ */
/*    ::FILE *fp = ::fopen(filename, access); */
/*    C4_CHECK_MSG(fp != nullptr, "could not open file"); */
/*    ::fwrite(buf, 1, sz, fp); */
/*    ::fclose(fp); */
/*} */
/*C4_SUPPRESS_WARNING_MSVC_POP */


/*void sample_parse_file() */
/*{ */
/*    const char filename[] = "ryml_example.yml"; */

/*    // because this is a minimal sample, it assumes nothing on the */
/*    // environment/OS (other than that it can read/write files). So we */
/*    // create the file on the fly: */
/*    file_put_contents(filename, ryml::csubstr("foo: 1\nbar:\n  - 2\n  - 3\n")); */

/*    // now we can load it into a std::string (for example): */
/*    { */
/*        std::string contents = file_get_contents<std::string>(filename); */
/*        ryml::Tree tree = ryml::parse_in_arena(ryml::to_csubstr(contents)); // immutable (csubstr) overload */
/*        C4_CHECK(tree["foo"].val() == "1"); */
/*        C4_CHECK(tree["bar"][0].val() == "2"); */
/*        C4_CHECK(tree["bar"][1].val() == "3"); */
/*        std::cout << tree["foo"].val() << " " << tree["bar"][0].val() << " " << tree["bar"][1].val() << std::endl; */
/*    } */
    
/*    /1* // or we can use a vector<char> instead: *1/ */
/*    /1* { *1/ */
/*    /1*     std::vector<char> contents = file_get_contents<std::vector<char>>(filename); *1/ */
/*    /1*     ryml::Tree tree = ryml::parse_in_place(ryml::to_substr(contents)); // mutable (csubstr) overload *1/ */
/*    /1*     C4_CHECK(tree["foo"].val() == "1"); *1/ */
/*    /1*     C4_CHECK(tree["bar"][0].val() == "2"); *1/ */
/*    /1*     C4_CHECK(tree["bar"][1].val() == "3"); *1/ */
/*    /1* } *1/ */

/*} */


/*/1* C4_SUPPRESS_WARNING_MSVC_POP *1/ */


/**
 * Compute the number (over 365) of a given day/month/year.
 *
 * day is exact (it starts at 1).
 * month starts at 0.
 * year is exact.
 */
int get_day_of_year(int day, int month, int year){
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


int main() {

    /* const char filename[] = "test.yaml"; */
    std::string filename = "/home/fitz/dev/Reminiscence/data/1/q1.yaml";
    
    /* Question a_question(filename); */
    /* a_question.print(); */
    /* int answer {a_question.ask_on_terminal()}; */
    /* if (answer == 0){ */
    /*     std::cout << "je dois appeler une méthode de la classe dailytask pour changer le dossier de cette question" << std::endl; */
    /* } */
    /* else{ */
    /*     std::cout << "je dois appeler une méthode de la classe dailytask pour changer le dossier de cette question" << std::endl; */
    /* } */

    std::filesystem::path data_folderName {"/home/fitz/dev/Reminiscence/data"};
    std::cout << data_folderName << std::endl;
    std::cout << "Absolute path: " << std::filesystem::absolute(data_folderName) << std::endl;
    std::cout << "fs::exists(data_folderName) : " << std::filesystem::exists(data_folderName) << std::endl;
    std::cout << "Content : full path" << std::endl;
    for (const auto & entry : std::filesystem::directory_iterator(data_folderName)){
        std::cout << entry.path() << std::endl;
    }
    std::cout << "Content : only filename" << std::endl;
    for (const auto & entry : std::filesystem::directory_iterator(data_folderName)){
        std::cout << entry.path().filename() << std::endl;
    }
    std::cout << "Is there a program.yaml file ?" << std::endl;
    for (const auto & entry : std::filesystem::directory_iterator(data_folderName)){
        if(entry.path().filename().string() == "program.yaml"){
            std::cout << "Yes !" << std::endl;
        }
    }
    std::cout << "What is the current day ?" << std::endl;
    // get current date, month, year. 
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    struct tm *parts = std::localtime(&now_c);
    int year    {1900 + parts->tm_year};
    int month   {parts->tm_mon};
    int day     {parts->tm_mday};
    std::cout << "day   = "   << day      << std::endl;
    std::cout << "month = " << month    << std::endl;
    std::cout << "year  = "  << year     << std::endl;
    std::cout << "What is the current day of the year ?" << std::endl;
    std::cout << "day of year: " << get_day_of_year(day, month, year) << std::endl;
    std::cout << "What are the task of this day ?" << std::endl;

    /* DailyTask task { data_folderName}; */




    /* sample_parse_file(); */

    /* std::cout << tmp::add(1, 3) << std::endl; */
    return 0;
}


