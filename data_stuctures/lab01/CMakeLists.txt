cmake_minimum_required(VERSION 3.10.0)
project(lab01 VERSION 0.1.0 LANGUAGES C CXX)

add_executable(lab01 src/main.cpp)
target_include_directories(lab01 PRIVATE include)
