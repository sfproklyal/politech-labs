cmake_minimum_required(VERSION 3.10.0)
project(course_work VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(course_work
    src/main.cpp
    src/LineList.cpp
    src/RedBlackTree.cpp
    src/CrossReferences.cpp
)
target_include_directories(course_work PRIVATE include)
