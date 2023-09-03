
enable_testing()
include(GoogleTest)

foreach(file ${test_sources})
    string(REGEX REPLACE "(.*/)([a-zA-Z0-9_ ]+)(\.cpp)" "\\2" test_name ${file}) 
    add_executable(${test_name}_Tests ${file})
    target_compile_features(${test_name}_Tests PUBLIC cxx_std_17)
    target_link_libraries(${test_name}_Tests gtest_main)
    gtest_discover_tests(${test_name}_Tests)
endforeach()


