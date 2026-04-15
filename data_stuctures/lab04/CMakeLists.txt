cmake_minimum_required(VERSION 3.10.0)
project(lab04 VERSION 0.1.0 LANGUAGES C CXX)

add_executable(lab04 src/main.cpp)
target_include_directories(lab04 PRIVATE include)
