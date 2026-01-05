#pragma once 
#include "Vehicle.hpp" 
#include "TelemetryManager.hpp"
#include <atomic>

class SimulationController { 
public: 
	SimulationController(); 
	
	void start();
	void pause();
	void resume();
	void stop();
	bool isRunning() const;
	void simulationLoop(Vehicle&, TelemetryManager&);

private: 
	std::atomic<bool> running;
	std::atomic<bool> paused;
};