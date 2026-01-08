cmake_minimum_required(VERSION 3.16) 

# If SimulationLib uses Qt types (QObject, signals/slots)
find_package(Qt6 REQUIRED COMPONENTS Core) 

add_library(SimulationLib 
	src/Battery.cpp
	src/Engine.cpp
	src/SimulationController.cpp 
	src/TelemetryManager.cpp
	src/Vehicle.cpp 

	include/Battery.hpp 
	include/Engine.hpp 
	include/SimulationController.hpp 
	include/TelemetryManager.hpp 
	include/Vehicle.hpp
) 

target_include_directories(SimulationLib PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include 
)

target_link_libraries(SimulationLib PUBLIC 
	Qt6::Core
)