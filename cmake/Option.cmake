#
# Project settings, executable and/or library and/or testing (with googletest)
#
option(${PROJECT_NAME}_BUILD_EXECUTABLE "Build the project as an executable." ON)
option(${PROJECT_NAME}_BUILD_LIBRARY_HEADERS_ONLY "Build the project as a header-only library" OFF)
option(${PROJECT_NAME}_ENABLE_UNIT_TESTING "Enable unit tests for the projects (from the `test` subfolder)." OFF)


#
# Compiler options
#
option(${PROJECT_NAME}_WARNINGS_AS_ERRORS "Treat compiler warnings as errors." ON)


#
# Static analyzers: currently supporting: Clang-Tidy, Cppcheck.
#
# 
option(${PROJECT_NAME}_ENABLE_CLANG_TIDY "Enable static analysis with Clang-Tidy." OFF)
option(${PROJECT_NAME}_ENABLE_CPPCHECK "Enable static analysis with Cppcheck." OFF)


#
# Code coverage.
# Tests are always enabled if the code coverage is enabled (see
# cmake/Utilities.cmake)
#
option(${PROJECT_NAME}_ENABLE_CODE_COVERAGE "Enable code coverage through GCC." OFF)


#
# Doxygen
#
option(${PROJECT_NAME}_ENABLE_DOXYGEN "Enable Doxygen documentation builds of source." ON)


#
# Generate compile_commands.json for clang based tools
#
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


#
# Enable usage of Ccache, in order to speed up rebuild time.
#
option(${PROJECT_NAME}_ENABLE_CCACHE "Enable the usage of Ccache, in order to speed up rebuild times." ON)



