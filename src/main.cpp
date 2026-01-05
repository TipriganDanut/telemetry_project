#include "Vehicle.hpp" 
#include "TelemetryManager.hpp" 
#include "SimulationController.hpp"
#include <iostream> 
#include <thread> 
#include <chrono> 
#include <conio.h> // for _kbhit()

int main() { 
	
	std::cout << "Controls:\n";
	std::cout << " P = pause\n";
	std::cout << " R = resume\n";
	std::cout << " Q = quit\n\n";

	Vehicle vehicle; 
	TelemetryManager telemetry(vehicle); 
	SimulationController controller;

	controller.start(); 
	std::thread simThread(&SimulationController::simulationLoop, &controller, std::ref(vehicle), std::ref(telemetry));

	while (controller.isRunning()) {
			// Handle keyboard commands 
			if (_kbhit()) {
				char key = _getch();
				if (key == 'p' || key == 'P') {
					controller.pause();
					std::cout << "[Simulation paused]\n";
				}
				else if (key == 'r' || key == 'R') {
					controller.resume();
					std::cout << "[Simulation resumed]\n";
				}
				else if (key == 'q' || key == 'Q') {
					controller.stop();
					std::cout << "[Simulation stopped]\n";
					break;
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
	simThread.join();
	return 0;
}