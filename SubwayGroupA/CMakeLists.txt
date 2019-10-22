cmake_minimum_required(VERSION 3.15)
project(module)

set(CMAKE_CXX_STANDARD 14)

add_executable(module main.cpp tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp tinystr.h tinyxml.h Station.cpp Station.h)