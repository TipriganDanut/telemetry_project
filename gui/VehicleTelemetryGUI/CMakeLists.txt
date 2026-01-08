find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Charts) 
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Charts) 

set(PROJECT_SOURCES 
	main.cpp 
	mainwindow.cpp 
	mainwindow.h 
	mainwindow.ui 
) 

qt_add_executable(VehicleTelemetryGUI 
	MANUAL_FINALIZATION 
	${PROJECT_SOURCES} 
) 

target_link_libraries(VehicleTelemetryGUI PRIVATE 
	SimulationLib 
	Qt6::Widgets 
	Qt6::Charts 
) 

qt_finalize_executable(VehicleTelemetryGUI)