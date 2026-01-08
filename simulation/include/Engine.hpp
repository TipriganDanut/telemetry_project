#pragma once 
class Engine { 
public: 
	Engine(); 

	int getRPM() const; 
	float getTemperature() const; 
	
	void update(); // simulate engine behavior 
private: 
	int rpm; 
	float temperature; 
};