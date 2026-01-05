#include "Vehicle.hpp" 
#include "TelemetryManager.hpp" 
#include "SimulationController.hpp"
#include <iostream> 
#include <thread> 
#include <chrono> 
#include <conio.h> // for _kbhit()

int main() { 
	Vehicle vehicle; 
	TelemetryManager telemetry(vehicle); 
	SimulationController controller;

	controller.run(vehicle, telemetry); 
	return 0;
}