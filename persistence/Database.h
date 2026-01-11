#pragma once 

#include <string> 
#include <sqlite3.h> 

class Database { 
public: 
	// Opens (or creates) the SQLite database file. 
	explicit Database(const std::string& path); 
	
	// Closes the database connection. 
	~Database(); 
	
	// Gives read-only access to the raw SQLite handle. 
	sqlite3* handle() const { return db_; } 

private: 
	// Creates tables and applies schema changes. 
	void runMigrations(); 

	sqlite3* db_ = nullptr; 
};