#pragma once 

struct TelemetryData { 
	int vehicleSpeed = 0;
	int rpm = 0;
	double engineTemperature = 0.0; 
	double batteryCharge = 0.0; 
	double batteryVoltage = 0.0;
	double batteryTemperature = 0.0;
	long long timestamp;
};