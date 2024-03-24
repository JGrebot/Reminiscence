#!/bin/zsh

if [ -d build ]; then
    rm -rf build
fi

mkdir build
cd build

# Using clang to get c++17 in language server support (LSP)
export CXX=/usr/bin/clang++
cmake ..
make -j 2
cp compile_commands.json ..
cd ..
