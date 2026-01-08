#pragma once 
#include "Vehicle.hpp"
#include "TelemetryData.hpp"
#include <string> 

class TelemetryManager { 
public: 
	TelemetryManager(Vehicle& vehicle); 
	TelemetryData collectData() const;
private: 
	Vehicle& vehicle; 
};