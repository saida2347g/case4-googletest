cmake_minimum_required(VERSION 3.16)
project(case4_googletest LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(GTest CONFIG QUIET)
if(NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

# Only compile tests: the assignment explicitly excludes implementation.
add_library(contract_tests OBJECT
    tests/queue_test.cpp tests/heap_test.cpp tests/binary_tree_test.cpp)
target_include_directories(contract_tests PRIVATE include)
target_link_libraries(contract_tests PRIVATE GTest::gtest)

# An optional implementation can be supplied later, outside this assignment.
set(IMPLEMENTATION_SOURCES "" CACHE STRING "Semicolon-separated implementation files")
if(IMPLEMENTATION_SOURCES)
    enable_testing()
    add_executable(unit_tests $<TARGET_OBJECTS:contract_tests> ${IMPLEMENTATION_SOURCES})
    target_include_directories(unit_tests PRIVATE include)
    target_link_libraries(unit_tests PRIVATE GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(unit_tests)
endif()
