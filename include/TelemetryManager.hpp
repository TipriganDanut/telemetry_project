#pragma once 
#include "Vehicle.hpp" 
#include <string> 

class TelemetryManager { 
public: 
	TelemetryManager(Vehicle& vehicle); 
	std::string collectData() const; 
private: 
	Vehicle& vehicle; 
};