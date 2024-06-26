#include "dailytask.hpp"
#include <question.hpp>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <ryml.hpp>
#include <ryml_std.hpp> 
#include <c4/format.hpp> 



std::string  presentation_string =R"( 
+ ~~~ + ~~~ + ~~~ + ~~~ + ~~~ + ~~~ + ~~~ + ~~~ + ~~~ + ~~~ + ~~~  +
  _____                _       _                             
 |  __ \              (_)     (_)                            
 | |__) |___ _ __ ___  _ _ __  _ ___  ___ ___ _ __   ___ ___ 
 |  _  // _ \ '_ ` _ \| | '_ \| / __|/ __/ _ \ '_ \ / __/ _ \
 | | \ \  __/ | | | | | | | | | \__ \ (_|  __/ | | | (_|  __/
 |_|  \_\___|_| |_| |_|_|_| |_|_|___/\___\___|_| |_|\___\___|

+ ~~~ + ~~~ + ~~~ + ~~~ + ~~~ + ~~~ + ~~~ + ~~~ + ~~~ + ~~~ + ~~~  +)";



C4_SUPPRESS_WARNING_MSVC_WITH_PUSH(4996) // fopen: this function or variable may be unsafe
/** load a file from disk and return a newly created CharContainer */
template<class CharContainer>
size_t file_get_contents(const char *filename, CharContainer *v)
{
    ::FILE *fp = ::fopen(filename, "rb");
    C4_CHECK_MSG(fp != nullptr, "could not open file");
    ::fseek(fp, 0, SEEK_END);
    long sz = ::ftell(fp);
    v->resize(static_cast<typename CharContainer::size_type>(sz));
    if(sz)
    {
        ::rewind(fp);
        size_t ret = ::fread(&(*v)[0], 1, v->size(), fp);
        C4_CHECK(ret == (size_t)sz);
    }
    ::fclose(fp);
    return v->size();
}


/** load a file from disk into an existing CharContainer */
template<class CharContainer>
CharContainer file_get_contents(const char *filename)
{
    CharContainer cc;
    file_get_contents(filename, &cc);
    return cc;
}


/** save a buffer into a file */
template<class CharContainer>
void file_put_contents(const char *filename, CharContainer const& v, const char* access)
{
    file_put_contents(filename, v.empty() ? "" : &v[0], v.size(), access);
}


/** save a buffer into a file */
void file_put_contents(const char *filename, const char *buf, size_t sz, const char* access)
{
    ::FILE *fp = ::fopen(filename, access);
    C4_CHECK_MSG(fp != nullptr, "could not open file");
    ::fwrite(buf, 1, sz, fp);
    ::fclose(fp);
}
C4_SUPPRESS_WARNING_MSVC_POP



void Question::parse_file(std::filesystem::path filename){
    std::string contents = file_get_contents<std::string>(filename.string().c_str());
    m_data = ryml::parse_in_arena(ryml::to_csubstr(contents)); // immutable (csubstr) overload
}



Question::Question(){
    ryml::Tree m_data {};
    m_name = "";
    m_folder = -1;
    m_not_already_asked = true;
    m_pDailyTask = nullptr;
}

Question::~Question(){ }




/**
 *  Constructor of a Question object from a yaml file.
 *
 *  Store the information from filename into the member m_data. The input file,
 *  filename, is expected to respect the required format.
 *
 *
 * @param filename   name of the yaml file containing the question and its
 *                   answer.
 */
Question::Question(std::filesystem::path filename, bool not_already_ask, DailyTask* p){
    //
    // filling m_data with filename content.
    this->parse_file(filename);
    m_name = filename;
    m_not_already_asked = not_already_ask;
    m_pDailyTask = p;
}



std::filesystem::path Question::get_path(){
    return m_name;
};


void Question::set_path(std::filesystem::path new_path){
    m_name = new_path;
};

bool Question::not_already_ask(){
    return m_not_already_asked;
};


/**
 * Ask the answer (y/n) of the question to the user. This function is recursive
 * until a character y or n is received.
 *
 *
 * @return 1 for good answer (y), or 0 for bad answer (n).
 */
int Question::get_answer_from_user() const{
    std::string input;
    do {
        std::cout << "Did you find the answer ? (y/n) ";
        std::getline(std::cin, input);
        if (input[0] == 'y'){
            std::cout << std::endl;
            return 1;
        }else if(input[0] == 'n'){
            std::cout << std::endl;
            return -1;
        }
    } while(1);
}


/**
 * Ask the question on terminal.
 *      - Clear the terminal.
 *      - Display the question.
 *      - display the answer after a user input.
 *
 *
 * @return answer: 1 for good response, -1 for bad response.
 */
int Question::ask_on_terminal(){
    system("clear");
    ryml::ConstNodeRef root = m_data.crootref();


    auto folderQuestion = m_pDailyTask->get_folderQuestion();
    int totalNumberQuestion {0};

    std::cout << "\033[1;34m" << presentation_string << "\033[0m" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "\033[1;32mFolder:\033[0m       " <<  m_pDailyTask->get_folderName() << std::endl;
    std::cout << "\033[1;32mDay:\033[0m          " <<  m_pDailyTask->get_programDay() << std::endl;
    std::cout << "\033[1;32mTasks:\033[0m        "; 
    bool to_display = false;
    for (auto& [key, vecQuestions] : folderQuestion) {
        for(auto iq = vecQuestions.begin(); iq != vecQuestions.end(); iq++){
            if(iq->not_already_ask()){
                to_display = true;
                totalNumberQuestion+=1;
            }
        }
        if(to_display){
            std::cout << key << " ";
        }
    }
    std::cout << std::endl;
    std::cout << "\033[1;32mTotal:\033[0m        " <<  totalNumberQuestion << std::endl;
    std::cout << "\033[1;32mResults\033[0m:      " << 
        m_pDailyTask->get_good_answer() << "/" <<
        m_pDailyTask->get_good_answer() + m_pDailyTask->get_wrong_answer() <<
        std::endl;
    std::cout << "\033[1;32mQuestion\033[0m:     " << m_name.filename().string() << std::endl;
    std::cout << std::endl;
    std::cout << "\033[32m" << root["question"].val() << "\033[0m" << std::endl;
    std::cout << std::endl;
    std::string tmp = "a";
    bool ok = false;
    do {
        std::cout << "Type Enter to get answer: ";
        std::getline(std::cin, tmp);
        (tmp.empty()) ? ok = true : ok = false;
    } while(!ok);
    std::cout << "Answer: " << std::endl;
    std::cout << "\033[32m" << root["answer"].val() << "\033[0m" << std::endl;
    std::cout << std::endl;
    m_not_already_asked = false;
    return this->get_answer_from_user();
}


/**
 * Display all the members of the object question on terminal. Used mainly for
 * debug purpose. 
 *
 */
void Question::print() const{

    ryml::ConstNodeRef root = m_data.crootref();

    // iterate children
    std::vector<ryml::csubstr> keys, vals; // to store all the root-level keys, vals
    for(ryml::ConstNodeRef n : root.children())
    {
        std::cout << n.key() << ": " ;
        if (n.has_val()){
            std::cout << n.val() << std::endl;
        }else{
            std::cout << std::endl;
        }
    }
}

