#include "Database.h"
#include <iostream> 

Database::Database(const std::string& path) { 
	// Open (or create) the SQLite database file 
	int result = sqlite3_open(path.c_str(), &db_); 
	if (result != SQLITE_OK) {
		std::cerr << "Failed to open database: " << sqlite3_errmsg(db_) << "\n"; 
		sqlite3_close(db_);  // close the half-open DB and throw
		db_ = nullptr; 
		throw std::runtime_error("Could not open SQLite database"); 
	} // if we hit throw, the constructor exits immediately
	
	// Apply schema and migrations 
	runMigrations(); 
} 

Database::~Database() { 
	if (db_) { // if db is opened
		sqlite3_close(db_); 
		db_ = nullptr; 
	} 
} 

void Database::runMigrations() {
	const char* sql = R"( 
		CREATE TABLE IF NOT EXISTS telemetry (
			id INTEGER PRIMARY KEY AUTOINCREMENT, 
			timestamp REAL NOT NULL, 
			speed REAL NOT NULL, 
			rpm REAL NOT NULL, 
			engine_temp REAL NOT NULL, 
			battery_voltage REAL NOT NULL 
			); 
		)"; 

	char* errorMsg = nullptr; 
	int result = sqlite3_exec(db_, sql, nullptr, nullptr, &errorMsg); 
	
	if (result != SQLITE_OK) {
		std::cerr << "Migration error: " << errorMsg << "\n"; 
		sqlite3_free(errorMsg); 
		throw std::runtime_error("Failed to run database migrations"); 
	} 
}