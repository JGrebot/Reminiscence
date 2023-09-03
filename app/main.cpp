#include <iostream>
#include <tmp.hpp>
#include <question.hpp>
#include <ryml.hpp>
#include <ryml_std.hpp> 
#include <c4/format.hpp> 
#include <iostream>
#include <sstream>
#include <vector>
#include <array>
#include <map>




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


void sample_parse_file()
{
    const char filename[] = "ryml_example.yml";

    // because this is a minimal sample, it assumes nothing on the
    // environment/OS (other than that it can read/write files). So we
    // create the file on the fly:
    file_put_contents(filename, ryml::csubstr("foo: 1\nbar:\n  - 2\n  - 3\n"));

    // now we can load it into a std::string (for example):
    {
        std::string contents = file_get_contents<std::string>(filename);
        ryml::Tree tree = ryml::parse_in_arena(ryml::to_csubstr(contents)); // immutable (csubstr) overload
        C4_CHECK(tree["foo"].val() == "1");
        C4_CHECK(tree["bar"][0].val() == "2");
        C4_CHECK(tree["bar"][1].val() == "3");
        std::cout << tree["foo"].val() << " " << tree["bar"][0].val() << " " << tree["bar"][1].val() << std::endl;
    }
    
    /* // or we can use a vector<char> instead: */
    /* { */
    /*     std::vector<char> contents = file_get_contents<std::vector<char>>(filename); */
    /*     ryml::Tree tree = ryml::parse_in_place(ryml::to_substr(contents)); // mutable (csubstr) overload */
    /*     C4_CHECK(tree["foo"].val() == "1"); */
    /*     C4_CHECK(tree["bar"][0].val() == "2"); */
    /*     C4_CHECK(tree["bar"][1].val() == "3"); */
    /* } */

}


/* C4_SUPPRESS_WARNING_MSVC_POP */

int main() {

    
    sample_parse_file();

    std::cout << tmp::add(1, 3) << std::endl;
    return 0;
}
