#pragma once 
#include "Vehicle.hpp" 
#include "TelemetryManager.hpp" 

class SimulationController { 
public: 
	SimulationController(); 
	
	void run(Vehicle& vehicle, TelemetryManager& telemetry);

private: 
	bool running;
	bool paused;
};