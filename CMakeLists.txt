cmake_minimum_required(VERSION 4.0)
project(OOP_lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_ASAN "Build with AddressSanitizer" OFF)
if(ENABLE_ASAN AND NOT MSVC)
    add_compile_options(-fsanitize=address -g)
    add_link_options(-fsanitize=address)
endif()

add_library(matrix_ops STATIC
        matrix_ops.h
        matrix_ops.cpp
)
target_include_directories(matrix_ops PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(OOP_lab1 main.cpp)
target_link_libraries(OOP_lab1 PRIVATE matrix_ops)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(OOP_lab1_tests test_variant.cpp)
target_link_libraries(OOP_lab1_tests PRIVATE matrix_ops GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(OOP_lab1_tests)