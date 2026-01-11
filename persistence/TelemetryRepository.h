#pragma once

#include "TelemetryData.hpp"
#include <sqlite3.h>
#include <vector>

class Database; // forward declaration to avoid circular dependency

class TelemetryRepository { //controller and UI will only talk to this repository, never to SQLite directly.	

public:
	explicit TelemetryRepository(const Database& db);

	void insert(const TelemetryData& data, double timestamp); // const because we don't want to modify/copy the TelemetryData passed 
	std::vector<TelemetryData> getLastN(int N); // retrieve the last N telemetry records from the database
private:
	sqlite3* db_;
	const Database& dbRef_;

};