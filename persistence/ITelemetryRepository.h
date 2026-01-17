#pragma once 

#include "TelemetryData.hpp" // adjust path if needed 
#include <vector> 

class ITelemetryRepository { 
public: 
	virtual ~ITelemetryRepository() = default; 
	
	virtual void saveTelemetry(const TelemetryData& data) = 0; 
	virtual std::vector<TelemetryData> loadAllTelemetry() const = 0; 
	virtual void clearTelemetry() = 0; 
};