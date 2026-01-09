#include "SimulationController.hpp"
#include "TelemetryData.hpp"
#include <iostream>
#include <thread>
#include <chrono> 

SimulationController::SimulationController(Vehicle& v, TelemetryManager& t)
	: running(false), /*This ensures the simulation thread won’t start doing anything until I explicitly call start() */
	paused(false),
	vehicle(v),		/* initialize reference - bind my member vehicle to refer to the object passed in as v */ 
	telemetry(t)	/* initialize reference - bind my member vehicle to refer to the object passed in as v */ {} 

void SimulationController::start() {
	if (running) {
		return; /* already running */
	}

	running = true; 
	paused = false;

	simThread = std::thread(&SimulationController::simulationLoop, this); /* creates the simulation thread for this SimulationController */
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
	if (!running) { 
		return; /* already stopped */
	}
	running = false;
	if (simThread.joinable())
		simThread.join();
}

void SimulationController::simulationLoop() {		
	while (running)	{
		if (paused)	{
			std::this_thread::sleep_for(std::chrono::milliseconds(100)); // thread sleeps instead of busy-waiting. Sleeping is cooperative and does not consume CPU 
			continue;
		}
		else
		{
			vehicle.update();
			TelemetryData data = telemetry.collectData();
			emit telemetryUpdated(data);
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
		}
	}

}
	
	
