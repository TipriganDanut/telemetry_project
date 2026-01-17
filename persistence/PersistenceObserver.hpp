#pragma once
#include "ITelemetryRepository.h"
#include "IObserver.h"

class PersistenceObserver : public IObserver { 
public: 
	explicit PersistenceObserver(ITelemetryRepository& repo);
	void update(const TelemetryData& data) override; 
	
private: 
	ITelemetryRepository& repo; 
};