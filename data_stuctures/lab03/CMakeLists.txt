cmake_minimum_required(VERSION 3.10.0)
project(lab03 VERSION 0.1.0 LANGUAGES C CXX)

add_executable(lab03 
    src/main.cpp
    src/checkBalanceBrackets.cpp
    )
target_include_directories(lab03 PRIVATE include)

