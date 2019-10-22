# This is the minimum version of CMake required before compiling this project.
cmake_minimum_required(VERSION 3.15)

# This is the name of our project.
project(Project)

# We're using C++ version 14.
set(CMAKE_CXX_STANDARD 14)

# Importing TinyXML files. Let's create a library instead? -22/10/19 (@cdecal)
set(TINYXML_FILES TinyXML/tinystr.cpp TinyXML/tinyxml.cpp TinyXML/tinyxmlerror.cpp TinyXML/tinyxmlparser.cpp TinyXML/tinystr.h TinyXML/tinyxml.h)

# We're declaring the source files here to keep everything organized.
set(SOURCE_FILES main.cpp main.cpp Station.cpp Station.h Tram.cpp Tram.h DesignByContract.h)

add_executable(Project ${SOURCE_FILES} ${TINYXML_FILES})