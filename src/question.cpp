#include <question.hpp>
#include <string>
#include <ryml.hpp>
#include <ryml_std.hpp> 
#include <c4/format.hpp> 
#include <stdlib.h>


// helper functions for sample_parse_file()
template<class CharContainer> CharContainer file_get_contents(const char *filename);
template<class CharContainer> size_t        file_get_contents(const char *filename, CharContainer *v);
template<class CharContainer> void          file_put_contents(const char *filename, CharContainer const& v, const char* access="wb");
void                                        file_put_contents(const char *filename, const char *buf, size_t sz, const char* access);






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


void Question::parse_file(const char * filename){
    std::string contents = file_get_contents<std::string>(filename);
    m_data = ryml::parse_in_arena(ryml::to_csubstr(contents)); // immutable (csubstr) overload
}



Question::Question(){
    ryml::Tree m_data {};
    std::string m_name {""};
    int m_folder {-1};
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
Question::Question(const char * filename){
    
    // filling m_data with filename content.
    this->parse_file(filename);
    std::string m_name {""};
    int m_folder {-1};
}


/**
 * Ask the answer (y/n) of the question to the user. This function is recursive
 * until a character y or n is received.
 *
 *
 * @return 1 for good answer (y), or 0 for bad answer (n).
 */
int Question::get_answer_from_user(){
    std::cout << "Did you find the answer ? (y/n) ";
    std::string input_from_console;
    std::cin >> input_from_console;
    if (input_from_console[0] == 'y'){
        std::cout << std::endl;
        return 1;
    }else if(input_from_console[0] == 'n'){
        std::cout << std::endl;
        return -1;
    }else{
        std::cout << std::endl;
        return this->get_answer_from_user();
    }
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
    std::cout << "Question: " << root["question"].val() << std::endl;
    std::cout << "Type any key to get answer: ";
    std::cin.get();
    std::cout << "Answer: " << root["answer"].val() << std::endl;
    return this->get_answer_from_user();
}


/**
 * Display all the members of the object question on terminal. Used mainly for
 * debug purpose. 
 *
 */
void Question::print(){

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

