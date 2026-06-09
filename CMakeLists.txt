cmake_minimum_required(VERSION 3.10)
project(lab06)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" OFF)

add_library(print STATIC sources/print.cpp)
target_include_directories(print PUBLIC include)

if(BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    add_executable(check tests/test_print.cpp)
    target_link_libraries(check print GTest::gtest_main)
    add_test(NAME check COMMAND check)
endif()

install(TARGETS print DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
