#include "PersistenceObserver.hpp"

PersistenceObserver::PersistenceObserver(ITelemetryRepository& repo) 
	: repo(repo) {} 

void PersistenceObserver::update(const TelemetryData& data) {
	repo.saveTelemetry(data); 
}