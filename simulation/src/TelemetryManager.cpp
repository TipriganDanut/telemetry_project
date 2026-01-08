#include "TelemetryManager.hpp"
#include <sstream> 

TelemetryManager::TelemetryManager(Vehicle& v) : 
	vehicle(v) {} 

TelemetryData TelemetryManager::collectData() const 
{ 
	TelemetryData data; 
	data.rpm = vehicle.getEngine().getRPM(); 
	data.engineTemperature = vehicle.getEngine().getTemperature(); 
	data.batteryCharge = vehicle.getBattery().getCharge(); 
	data.batteryVoltage = vehicle.getBattery().getVoltage(); 
	return data; 
}