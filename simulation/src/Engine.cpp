#include "Engine.hpp" 
#include <random>
Engine::Engine() : rpm(0), temperature(20.0f) {} 
	int Engine::getRPM() const { return rpm; } 
	float Engine::getTemperature() const { return temperature; } 
	
	void Engine::update() { 
		static std::random_device rd; 
		static std::mt19937 gen(rd()); 
		
		std::uniform_int_distribution<int> rpmDist(1000, 5000); 
		std::uniform_real_distribution<float> tempDist(85.0f, 105.0f); // Celsius
		rpm = rpmDist(gen); 
		temperature = tempDist(gen);
	}