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

