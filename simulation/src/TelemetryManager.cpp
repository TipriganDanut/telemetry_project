#include "TelemetryManager.hpp" 

TelemetryManager::TelemetryManager(Vehicle& v) : 
	vehicle(v) {} 

TelemetryData TelemetryManager::collectData() const 
{ 
	TelemetryData data; 
	data.rpm = vehicle.getEngine().getRPM(); 
	data.engineTemperature = vehicle.getEngine().getTemperature();

	data.vehicleSpeed = data.rpm * 0.02; // placeholder relationship

	data.batteryCharge = vehicle.getBattery().getCharge(); 
	data.batteryVoltage = vehicle.getBattery().getVoltage(); 
	data.batteryTemperature = vehicle.getBattery().getTemperature();

	return data; 
}