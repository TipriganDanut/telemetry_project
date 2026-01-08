cmake_minimum_required(VERSION 3.16) 
project(telemetry_project LANGUAGES CXX) 

set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON) 
set(CMAKE_AUTORCC ON)

add_subdirectory(simulation) 
add_subdirectory(gui/VehicleTelemetryGUI)