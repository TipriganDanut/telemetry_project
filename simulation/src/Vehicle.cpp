#include "Vehicle.hpp" 
Vehicle::Vehicle() {} 

Engine& Vehicle::getEngine() { return engine; } 
Battery& Vehicle::getBattery() { return battery; } 
void Vehicle::update() { 
	engine.update(); 
	battery.update(); 
}