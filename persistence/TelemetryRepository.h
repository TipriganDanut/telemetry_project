#pragma once

#include "TelemetryData.hpp"
#include "ITelemetryRepository.h"
#include <sqlite3.h>
#include <vector>

class Database; // forward declaration to avoid circular dependency

class TelemetryRepository : public ITelemetryRepository { //controller and UI will only talk to this repository, never to SQLite directly.	

public:
	explicit TelemetryRepository(const Database& db);

	void saveTelemetry(const TelemetryData& data); // will insert a row into the SQLite database
	std::vector<TelemetryData> loadAllTelemetry() const; // will query all rows from your SQLite database and return them as a vector of TelemetryData
	void clearTelemetry(); // will delete all rows from the SQLite database
	
	
private:
	sqlite3* db_;
	const Database& dbRef_;

	void insert(const TelemetryData& data, double timestamp); // for keeping SQL out of the public methods
	std::vector<TelemetryData> getLastN(int N); // retrieve the last N telemetry records from the database

};