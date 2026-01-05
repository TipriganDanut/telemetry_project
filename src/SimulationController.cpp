#include "SimulationController.hpp"
#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono> 

SimulationController::SimulationController() 
	: running(false), paused(false) {}

void SimulationController::run(Vehicle& vehicle, TelemetryManager& telemetry) {
	running = true; paused = false; 
	
	std::cout << "Controls:\n"; 
	std::cout << " P = pause\n"; 
	std::cout << " R = resume\n"; 
	std::cout << " Q = quit\n\n"; 
	
	// Clear buffered keys 
	while (_kbhit()) _getch(); 
	while (running) { 
		// Handle keyboard commands 
		if (_kbhit()) {
			char key = _getch();
			if (key == 'p' || key == 'P') {
				paused = true; 
				std::cout << "[Simulation paused]\n";
			} else if (key == 'r' || key == 'R') {
				paused = false; 
				std::cout << "[Simulation resumed]\n"; 
			} else if (key == 'q' || key == 'Q') {
				running = false; 
				break; 
			} 
		} 
		if (!paused) { 
				vehicle.update(); 
				std::cout << telemetry.collectData() << std::endl; 
		} 
		std::this_thread::sleep_for(std::chrono::seconds(1)); 
	} 
	std::cout << "Simulation stopped.\n"; 
}