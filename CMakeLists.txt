cmake_minimum_required(VERSION 3.10.2)
set(project_name neuralnetwork)
project(${project_name})

set(CMAKE_CXX_STANDARD 17)
# Don't allow cmake to fallback to an earlier C++ version:
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# gcc flags.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wno-long-long -pedantic -Wshadow -Wno-unused-variable -DNDEBUG")
#-no-long-long # Why was this needed?


# Conan
if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to
            run conan install first")
endif()

# 3rd-party
set(3RD_PARTY_DIR ${PROJECT_SOURCE_DIR}/3rdparty)

# The recommendation against GLOB describes the issue whereby adding a
# new file will not instruct the build system that a project has changed.
# However, seeing as this is a 1-person project and Clion is being used, this
# issue doesn't seem relevant. So let's use GLOB until this situation changes.

# Library
file(GLOB_RECURSE source_list "${PROJECT_SOURCE_DIR}/*.cpp"
                              "${PROJECT_SOURCE_DIR}.hpp")
add_library(${project_name} ${source_list})
target_include_directories(${project_name}
                           PUBLIC
                           ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(${project_name} ${CONAN_LIBS})

# Tests
set(project_test_dir "${PROJECT_SOURCE_DIR}/test")
file(GLOB_RECURSE test_source_list "${project_test_dir}/*.cpp"
                                   "${project_test_dir}/*.hpp")
add_executable(runTests ${test_source_list})
target_link_libraries(runTests gtest gtest_main)
target_link_libraries(runTests ${CONAN_LIBS})
target_link_libraries(runTests ${project_name})
target_include_directories(runTests
                           PRIVATE
                           ${project_test_dir}/common)
enable_testing()
# Add a test to the project to be run by ctest
#add_test(<name> <executable>)
add_test(gtests runTests)


