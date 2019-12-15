cmake_minimum_required(VERSION 3.6)
project(SubwaySimulation)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Werror -O2")
set(CMAKE_EXE_LINKER_FLAGS -pthread)
if(WIN32)
     include_directories(gtest-windows/include)
     link_directories(gtest-windows/lib)
elseif(APPLE)
    include_directories(gtest/include)
    link_directories(gtest/lib)
else()
    include_directories(gtest-linux/include)
    link_directories(gtest-linux/lib)
endif()

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp Subway.cpp Station.cpp Tram.cpp SubwaySimulationImporter.cpp SubwaySimulationMain.cpp SubwaySimulationUtils.cpp SubwaySimulationExporter.cpp Track.cpp)

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp SubwaySimulationTests.cpp SubwaySimulationDomainTests.cpp Subway.cpp Station.cpp Tram.cpp SubwaySimulationDomainTests.cpp SubwaySimulationImporter.cpp SubwaySimulationInputTests.cpp SubwaySimulationUtils.cpp SubwaySimulationOutputTests.cpp SubwaySimulationMovingTests.cpp SubwaySimulationExporter.cpp Track.cpp)

# Create RELEASE target
add_executable(release ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(debug ${DEBUG_SOURCE_FILES})

# Link library$
target_link_libraries(debug gtest)
include_directories(testInput)
include_directories(testOutput)
include_directories(testSimulation)
include_directories(userFiles)

file(COPY testOutput DESTINATION ..)
file(COPY testInput DESTINATION ..)
file(COPY testSimulation DESTINATION ..)
file(COPY userFiles DESTINATION ..)
file(COPY testCSV DESTINATION ..)
