
include(FetchContent)

#
# googletest
#
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Only done in test/CMakeLists.txt
# FetchContent_MakeAvailable(googletest)



#
# rapidyaml
#

set(RYML_BRANCH_NAME master)
FetchContent_Declare(ryml
    GIT_REPOSITORY https://github.com/biojppm/rapidyaml.git
    GIT_TAG ${RYML_BRANCH_NAME}
    GIT_SHALLOW FALSE  # ensure submodules are checked out
)

FetchContent_MakeAvailable(ryml)



