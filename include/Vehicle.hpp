#pragma once 
#include "Engine.hpp" 
#include "Battery.hpp" 
class Vehicle { 
public: 
	Vehicle(); 
	Engine& getEngine(); 
	Battery& getBattery(); 

	void update(); 

private: 
	Engine engine; 
	Battery battery; 
};