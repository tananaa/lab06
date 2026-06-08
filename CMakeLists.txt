cmake_minimum_required(VERSION 3.10)
project(lab05)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" OFF)

add_subdirectory(banking)

if(BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    
    add_executable(check 
        tests/test_account.cpp
        tests/test_transaction.cpp
    )
    target_link_libraries(check banking GTest::gtest_main)
    target_include_directories(check PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    add_test(NAME check COMMAND check)
endif()
