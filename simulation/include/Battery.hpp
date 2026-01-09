#pragma once 
class Battery { 
public: 
	Battery(); 
	
	float getCharge() const; 
	float getVoltage() const; 
	float getTemperature() const;

	void update(); // simulate battery behavior 
private: 
	float charge; 
	float voltage;
	float temperature;
};