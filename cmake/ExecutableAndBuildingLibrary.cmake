


# For building an executable
if(${PROJECT_NAME}_BUILD_EXECUTABLE)

    add_executable(${PROJECT_NAME} ${exe_sources})

    set_target_properties(
        ${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    )

    target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )
endif()


# For building a library (if tests are enabled OR if a library is built)
if(${PROJECT_NAME}_BUILD_LIBRARY_HEADERS_ONLY OR ${PROJECT_NAME}_ENABLE_UNIT_TESTING)

    add_library(
        ${PROJECT_NAME}_LIB
        ${headers}
        ${sources}
    )

    set_target_properties(
        ${PROJECT_NAME}_LIB
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        OUTPUT_NAME ${PROJECT_NAME}
    )

    target_include_directories(
        ${PROJECT_NAME}_LIB
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )
endif()



