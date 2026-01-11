cmake_minimum_required(VERSION 3.16) 
project(telemetry_project LANGUAGES C CXX) 

# Disable Qt Creator auto-setup script 
set(CMAKE_PROJECT_INCLUDE_BEFORE "" CACHE STRING "" FORCE)

# Global settings
set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON) 
set(CMAKE_AUTORCC ON)

# Optional module toggles 
option(ENABLE_PERSISTENCE "Enable Persistence module" ON) 
option(ENABLE_SIMULATION "Enable Simulation module" ON) 
option(ENABLE_GUI "Enable GUI module" ON)

find_package(Qt6 REQUIRED COMPONENTS Core) 
qt_standard_project_setup()

# Third-party: SQLite (standalone target) 
add_library(sqlite3 STATIC 
    ${CMAKE_SOURCE_DIR}/third_party/sqlite/sqlite3.c 
) 

set_target_properties(sqlite3 
    PROPERTIES AUTOMOC OFF
) 

target_include_directories(sqlite3 PUBLIC 
    ${CMAKE_SOURCE_DIR}/third_party/sqlite 
)

# Add modules conditionally 
if(ENABLE_PERSISTENCE) 
    add_subdirectory(persistence) 
endif() 

if(ENABLE_SIMULATION) 
    add_subdirectory(simulation) 
endif() 
if(ENABLE_GUI) 
    # Find Qt 
    find_package(Qt6 REQUIRED COMPONENTS Widgets) 
    add_subdirectory(gui/VehicleTelemetryGUI) 
endif()


