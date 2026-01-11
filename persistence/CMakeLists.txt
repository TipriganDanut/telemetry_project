cmake_minimum_required(VERSION 3.16)

add_library(PersistenceLib 
	Database.cpp 
	TelemetryRepository.cpp 
) 

target_include_directories(PersistenceLib PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/simulation/include 
	${CMAKE_SOURCE_DIR}/third_party/sqlite 
) 

target_link_libraries(PersistenceLib PUBLIC 
	Qt6::Core
	sqlite3
)