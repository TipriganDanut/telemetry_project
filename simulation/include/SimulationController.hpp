#pragma once 
#include "Vehicle.hpp" 
#include "TelemetryManager.hpp"
#include "ITelemetryRepository.h"
#include "ISubject.h"
#include <atomic>
#include <QObject>
#include <thread>

struct TelemetryData;

class SimulationController : public QObject, public ISubject {
	Q_OBJECT
public: 
	explicit SimulationController(Vehicle& v, TelemetryManager& t, ITelemetryRepository& repo);
	
	void start();
	void pause();
	void resume();
	void stop();
	bool isRunning() const;

	// ISubject overrides 
	void attach(IObserver* obs) override;
	void detach(IObserver* obs) override;
	void notify(const TelemetryData& data) override;
	

private: 
	void simulationLoop();

	std::atomic<bool> running;
	std::atomic<bool> paused;

	Vehicle& vehicle;
	TelemetryManager& telemetry;

	std::thread simThread;

	ITelemetryRepository& repo;

	std::vector<IObserver*> observers; // <— required by ISubject

signals: 
	void telemetryUpdated(const TelemetryData& data);
};