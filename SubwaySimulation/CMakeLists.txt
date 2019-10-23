# This is the minimum version of CMake required before compiling this project.
cmake_minimum_required(VERSION 3.15)
project(SubwaySimulation)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Werror -O2")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(../gtest/include)

# Set Library dir
link_directories(gtest/lib)

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp Subway.cpp Station.cpp Station.h Tram.cpp Tram.h)

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp Subway.cpp Station.cpp Station.h Tram.cpp Tram.h)

# Create RELEASE target
add_executable(release ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(debug ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(debug gtest)

file(COPY testOutput DESTINATION .)
file(COPY testInput DESTINATION .)