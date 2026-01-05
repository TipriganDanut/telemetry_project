#include "TelemetryManager.hpp"
#include <sstream> 

TelemetryManager::TelemetryManager(Vehicle& v) : vehicle(v) {} 

std::string TelemetryManager::collectData() const { 
	std::stringstream ss; 
	ss << "RPM: " << vehicle.getEngine().getRPM() << "\n"; 
	ss << "Engine Temp: " << vehicle.getEngine().getTemperature() << " °C\n"; 
	ss << "Battery Charge: " << vehicle.getBattery().getCharge() << "%\n"; 
	ss << "Battery Voltage: " << vehicle.getBattery().getVoltage() << " V\n"; 
	return ss.str(); 
}