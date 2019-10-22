# This is the minimum version of CMake required before compiling this project.
cmake_minimum_required(VERSION 3.15)

# This is the name of our project.
project(Project)

# We're using C++ version 14.
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp main.cpp tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp tinystr.h tinyxml.h Station.cpp Station.h)

add_executable(Project ${SOURCE_FILES})