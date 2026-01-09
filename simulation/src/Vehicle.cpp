#include "Vehicle.hpp" 
Vehicle::Vehicle() {} 

Engine& Vehicle::getEngine() { 
	return engine; 
} 
Battery& Vehicle::getBattery() { 
	return battery; 
} 
int Vehicle::getVehicleSpeed() const { 
	return this->vehicleSpeed;
}
void Vehicle::update() { 
	engine.update(); 
	battery.update(); 
}