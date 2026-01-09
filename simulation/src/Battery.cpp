#include "Battery.hpp" 
#include <random>
Battery::Battery() : charge(100.0f), voltage(12.6f) {} 

float Battery::getCharge() const { return charge; } 
float Battery::getVoltage() const { return voltage; } 
float Battery::getTemperature() const { return this->temperature; }

void Battery::update() { 
	static std::random_device rd;
	static std::mt19937 gen(rd());

	std::uniform_real_distribution<float> drainDist(0.05f, 0.2f);

	charge -= drainDist(gen); 
	if (charge < 0) 
		charge = 0;

	voltage = 12.0f + (charge / 100.0f) * 0.6f;
}