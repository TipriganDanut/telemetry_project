#include "SimulationController.hpp"
#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono> 

SimulationController::SimulationController() 
	: running(false), paused(false) {} // This ensures the simulation thread won’t start doing anything until I explicitly call start()

void SimulationController::start() {
	running = true; paused = false;
}

bool SimulationController::isRunning() const {
	return running; 
}

void SimulationController::pause() {
	paused = true;	
}
void SimulationController::resume() {
	paused = false;
}
void SimulationController::stop() {
	running = false;
}

void SimulationController::simulationLoop(Vehicle& vehicle, TelemetryManager& telemetry) {
	{		
		while (running)
		{
			if (paused)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
			else
			{
				vehicle.update();
				std::cout << telemetry.collectData() << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}
		}

	}
	
	
}