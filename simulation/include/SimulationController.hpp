#pragma once 
#include "Vehicle.hpp" 
#include "TelemetryManager.hpp"
#include <atomic>
#include <QObject>
#include <thread>

struct TelemetryData;

class SimulationController : public QObject {
	Q_OBJECT
public: 
	explicit SimulationController(Vehicle&, TelemetryManager&);
	
	void start();
	void pause();
	void resume();
	void stop();
	bool isRunning() const;
	

private: 
	void simulationLoop();

	std::atomic<bool> running;
	std::atomic<bool> paused;

	Vehicle& vehicle;
	TelemetryManager& telemetry;

	std::thread simThread;

signals: 
	void telemetryUpdated(const TelemetryData& data);
};