cmake_minimum_required(VERSION 3.10.0)
project(labT4 VERSION 0.1.0 LANGUAGES C CXX)


add_executable(labT4 src/main.cpp src/rectangle.cpp src/rhombus.cpp src/composite_shape.cpp)
target_include_directories(labT4 PRIVATE include)
