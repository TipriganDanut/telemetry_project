cmake_minimum_required(VERSION 3.16) 
project(TelemetryProject LANGUAGES CXX) 

# Use modern C++20
set(CMAKE_CXX_STANDARD 20) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include/ directory for headers 
include_directories(${PROJECT_SOURCE_DIR}/include)

# Collect all .cpp files automatically 
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp" )

# Create the executable 
add_executable(telemetry ${SOURCES})