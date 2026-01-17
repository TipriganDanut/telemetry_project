#include "TelemetryRepository.h"
#include "Database.h"
#include <sqlite3.h>
#include <stdexcept>
#include <iostream>

TelemetryRepository::TelemetryRepository(const Database& db)
    : dbRef_(db), db_(db.handle()) {}// store/initialize reference to Database and get raw SQLite handle and store that pointer in db_

void TelemetryRepository::saveTelemetry(const TelemetryData& data) { 
    // extract timestamp from the data 
    double timestamp = data.timestamp; 
    // delegate to your private helper 
    insert(data, timestamp); 
}

void checkSqlite(int result, sqlite3* db, const char* message) {
    if (result != SQLITE_OK) {
        throw std::runtime_error(std::string(message) + ": " + sqlite3_errmsg(db));
    }
}

void checkStep(int result, sqlite3* db, const char* message) { // If something goes wrong, the function never returns � it throws, thus a return value becomes meaningless.
    if (result != SQLITE_DONE && result != SQLITE_ROW) {
        throw std::runtime_error(std::string(message) + ": " + sqlite3_errmsg(db));
    }
}

std::vector<TelemetryData> TelemetryRepository::loadAllTelemetry() const {
    std::vector<TelemetryData> results;
    const char* sql = "SELECT timestamp, speed, rpm, engine_temp, battery_voltage FROM telemetry"; 
    sqlite3_stmt* stmt = nullptr; 
    checkSqlite(sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr), db_, "Failed to prepare loadAllTelemetry");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        TelemetryData data; 
        data.timestamp = sqlite3_column_double(stmt, 0); 
        data.vehicleSpeed = sqlite3_column_int(stmt, 1);
        data.rpm = sqlite3_column_int(stmt, 2); 
        data.engineTemperature = sqlite3_column_double(stmt, 3);
        data.batteryVoltage = sqlite3_column_double(stmt, 4);
        results.push_back(data);
    } sqlite3_finalize(stmt);
        return results; 
}

void TelemetryRepository::clearTelemetry() { 
    const char* sql = "DELETE FROM telemetry"; 
    char* errMsg = nullptr; 
    int result = sqlite3_exec(db_, sql, nullptr, nullptr, &errMsg); 
    if (result != SQLITE_OK) { 
        std::string msg = "Failed to clear telemetry: "; 
        msg += errMsg ? errMsg : "";
        sqlite3_free(errMsg); 
        throw std::runtime_error(msg);
    } 
}

void TelemetryRepository::insert(const TelemetryData& data, double timestamp) {
    const char* sql = R"(
        INSERT INTO telemetry (timestamp, speed, rpm, engine_temp, battery_voltage)
        VALUES (?, ?, ?, ?, ?);
        )";

    sqlite3_stmt* stmt = nullptr;

    int result = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    checkSqlite(result, db_, "Failed to prepare insert statement");

    checkSqlite(sqlite3_bind_double(stmt, 1, timestamp), db_, "Failed to bind timestamp");
    checkSqlite(sqlite3_bind_int(stmt, 2, data.vehicleSpeed), db_, "Failed to bind vehicle speed");
    checkSqlite(sqlite3_bind_int(stmt, 3, data.rpm), db_, "Failed to bind engine RPM");
    checkSqlite(sqlite3_bind_double(stmt, 4, data.engineTemperature), db_, "Failed to bind engine temperature");
    checkSqlite(sqlite3_bind_double(stmt, 5, data.batteryVoltage), db_, "Failed to bind battery voltage");

    result = sqlite3_step(stmt);
    checkStep(result, db_, "Failed to step insert statement");

    sqlite3_finalize(stmt);
}

std::vector<TelemetryData> TelemetryRepository::getLastN(int N) {

    std::vector<TelemetryData> results;

    const char* sql = "SELECT timestamp, speed, rpm, engine_temp, battery_voltage FROM telemetry ORDER BY timestamp DESC LIMIT ?"; // SQL query to get last N records ordered by timestamp descending - newest first

    sqlite3_stmt* stmt = nullptr;

    checkSqlite(sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr), db_, "prepare failed: ");

    checkSqlite(sqlite3_bind_int(stmt, 1, N), db_, "bind N failed: ");

    while (sqlite3_step(stmt) == SQLITE_ROW) { // while there are rows to process, step through each row in the result set
        // Read columns into a TelemetryData object
        TelemetryData data;

        data.timestamp = sqlite3_column_double(stmt, 0);
        data.vehicleSpeed = sqlite3_column_int(stmt, 1);
        data.rpm = sqlite3_column_int(stmt, 2);
        data.engineTemperature = sqlite3_column_double(stmt, 3);
        data.batteryVoltage = sqlite3_column_double(stmt, 4);

        results.push_back(data); // Add TelemetryData object contents to results

    }

    sqlite3_finalize(stmt);
    return results;
}
