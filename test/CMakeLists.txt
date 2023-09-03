

# If tests are enable in the cmake/Option.cmake.
if(${PROJECT_NAME}_ENABLE_UNIT_TESTING)

    FetchContent_MakeAvailable(googletest)

    enable_testing()
    include(GoogleTest)

    foreach(file ${test_sources})
        string(REGEX REPLACE "(.*/)([a-zA-Z0-9_ ]+)(\.cpp)" "\\2" test_name ${file}) 
        add_executable(${test_name}_Tests ${file})
        target_compile_features(${test_name}_Tests PUBLIC cxx_std_17)
        target_link_libraries(${test_name}_Tests gtest_main)
        gtest_discover_tests(${test_name}_Tests)


        #
        # Setup code coverage if enabled
        #
        if (${CMAKE_PROJECT_NAME}_ENABLE_CODE_COVERAGE)
            target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -O0 -g -fprofile-arcs -ftest-coverage)
            target_link_options(${CMAKE_PROJECT_NAME} PUBLIC -fprofile-arcs -ftest-coverage)
        endif()

    endforeach()
endif()


