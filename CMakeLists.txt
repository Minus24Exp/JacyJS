cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(GCC_COVERAGE_COMPILE_FLAGS "ggdb -g -O3 -coverage -fprofile-arcs -ftest-coverage")
set(GCC_COVERAGE_LINK_FLAGS "-coverage -lgcov")

project(Jacy VERSION 0.0.1)

file(GLOB_RECURSE SOURCES src/**/*.cpp src/*.cpp)
include_directories(include/)
add_executable(${PROJECT_NAME} ${SOURCES} include/translator/Translator.h src/translator/Translator.cpp)
