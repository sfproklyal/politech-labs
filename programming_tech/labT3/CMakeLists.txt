cmake_minimum_required(VERSION 3.10.0)
project(labT3 VERSION 0.1.0 LANGUAGES CXX)

add_executable(labT3
  src/main.cpp
  src/polygon.cpp
  src/methods.cpp
  src/commands.cpp
)
target_include_directories(labT3 PRIVATE include)
