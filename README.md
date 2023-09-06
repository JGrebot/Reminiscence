# TODO
I/O module (just un fichier cpp)
- a function to get all the question file name, from a specific folder.
- a function to read a yaml question/answer file, saving also the filename.
- a function to read all yaml question/answer file from a folder. Output a structure of type ryml::Tree
- a function to move the file from a folder X to a folder Y.

## Dependency

- rapid-yml from https://github.com/biojppm/rapidyaml . 
    - Fetched and compiled on the fly.
- cmd_line_parser from https://github.com/jermp/cmd_line_parser/tags .
    - Header only library, v1.0.1 is already in the include folder.




Une classe Daily_Task
    private:
        constructor (from a relative path std::string)
        get_folder_from_current_day
        get_all_questions 
        save_all_answer
    public:
        ask_all_question (appelle save_all_answer)
        m_all_question (vector of question)
        


main.cpp
    Creer une Daily_Task("le/chemin")
    ask_all_question()
    return 0;



main.cpp
1. Get the folder number to proceed (checking with the day of the month,  and a
   yaml file to map the month day to a list of folder. write this file with
   python, also generate the same for 365 day (passing to 2/3 month at the end)
2. Launch the tests for all required folder.
3. Launch each test
    - clean the terminal console.
    - display the question.
    - display the answer, and question, good/wrong answer. (and move the file according to the answer)
4. main optional console argument (the data folder, and a list of folder number (if a full fresh is needed)
5. store the results in a yaml file for statistics. Number of good answer overall and per folder.




# Reminiscence
Reminiscence is a learning app, based on the spaced repetition and the auto-test principle.

## Compilation
First set the compilation option in cmake/Option.cmake (an executable, a
library and/or the test). Then type
```bash
mkdir build && cd build && cmake .. && make -j 2
```


## Doxygen
On Ubuntu, install with:
```bash
sudo apt install doxygen
```
Enable Doxygen documentation build of source (see cmake/Option.cmake) and compile.
Then, in the build directory, type 
```bash
doxygen Doxyfile.doxygen-docs
```
Go to the created docs folder and open the index.html file in a browser.


## clang format
On Ubuntu, install clang and clang-format with:
```bash
sudo apt install clang && sudo apt install clang-format
```

With clang-format, format the code using:
```bash
find . -type f \( -name "*.cpp" -o -name "*.hpp" \) -exec clang-format -i {} \;
```
in the main directory.

