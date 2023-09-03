cmake_minimum_required(VERSION 3.14)
project(
    "Reminiscence"
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)


# All cmake options
include(cmake/Option.cmake)

# Fetch dependency
include(cmake/Fetch.cmake)

# Various cmake utilities: Clang tidy, cppcheck, doxygen and Ccache (if
# activated in cmake/Option.cmake) and some settings: default build type,
# prevent building in the source directory, always enabling the test if code
# coverage is enabled.
include(cmake/Utilities.cmake)

# Set sources and headers.
include(cmake/SourcesAndHeaders.cmake)

# Adding executable (or resulting library)
include(cmake/ExecutableAndBuildingLibrary.cmake)

# Adding tests
add_subdirectory(test)

