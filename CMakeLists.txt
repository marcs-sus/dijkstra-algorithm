cmake_minimum_required(VERSION 3.10)
project(dijkstra-algorithm)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Source files
file(GLOB SOURCES "src/*.cpp")

# Add executable
add_executable(dijkstra ${SOURCES})

# Copy the graphs directory
add_custom_command(TARGET dijkstra POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/graphs $<TARGET_FILE_DIR:dijkstra>/graphs)
