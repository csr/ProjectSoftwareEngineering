# This is the minimum version of CMake required before compiling this project.
cmake_minimum_required(VERSION 3.6)
project(SubwaySimulation)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Werror -O2")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

if(WIN32)
    # Set include dir
    include_directories(gtest-windows/include)
    # Set Library dir
    link_directories(gtest-windows/lib)
elseif(APPLE)
   include_directories(gtest/include)
   link_directories(gtest/lib)

else()
    # Set include dir
    include_directories(gtest-linux/include)
    # Set Library dir
    link_directories(gtest-linux/lib)
endif()

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp Subway.cpp Station.cpp Tram.cpp SubwaySimulationImporter.cpp SubwaySimulationMain.cpp SubwaySimulationExporter.cpp)

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp SubwaySimulationTests.cpp SubwaySimulationDomainTests.cpp Subway.cpp Station.cpp Tram.cpp SubwaySimulationDomainTests.cpp SubwaySimulationImporter.cpp SubwaySimulationInputTests.cpp SubwaySimulationExporter.cpp SubwaySimulationUtils.cpp SubwaySimulationOutputTests.cpp SubwaySimulationMovingTests.cpp)

# Create RELEASE target
add_executable(release ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(debug ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(debug gtest)

include_directories(testInput)
include_directories(testOutput)
include_directories(testSimulation)

file(COPY testOutput DESTINATION .)
file(COPY testInput DESTINATION .)
file(COPY testSimulation DESTINATION .)
