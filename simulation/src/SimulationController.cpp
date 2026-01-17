#include "SimulationController.hpp"
#include "TelemetryData.hpp"
#include "IObserver.h"
#include <thread>
#include <chrono> 

SimulationController::SimulationController(Vehicle& v, TelemetryManager& t, ITelemetryRepository& r)
	: running(false), /*This ensures the simulation thread won’t start doing anything until I explicitly call start() */
	paused(false),
	vehicle(v),		/* initialize reference - bind my member vehicle to refer to the object passed in as v */ 
	telemetry(t),	/* initialize reference - bind my member vehicle to refer to the object passed in as v */
	repo(r) /* repository bound to this DB */ {} 

void SimulationController::start() {
	if (running) {
		return; /* already running */
	}

	running = true; 
	paused = false;

	simThread = std::thread(&SimulationController::simulationLoop, this); /* creates the simulation thread for this SimulationController */
}

bool SimulationController::isRunning() const {
	return running; 
}

void SimulationController::pause() {
	paused = true;	
}
void SimulationController::resume() {
	paused = false;
}
void SimulationController::stop() {
	if (!running) { 
		return; /* already stopped */
	}
	running = false;
	if (simThread.joinable())
		simThread.join();
}

void SimulationController::simulationLoop() {		
	while (running)	{
		if (paused)	{
			std::this_thread::sleep_for(std::chrono::milliseconds(100)); // thread sleeps instead of busy-waiting. Sleeping is cooperative and does not consume CPU 
			continue;
		}
		else
		{
			// Update vehicle state
			vehicle.update();

			// Collect telemetry snapshot
			TelemetryData data = telemetry.collectData();

			// Notify configured observers - broadcast the new data
			notify(data);

			// Notify GUI
			emit telemetryUpdated(data);

			std::this_thread::sleep_for(std::chrono::milliseconds(250));
		}
	}

}

void SimulationController::attach(IObserver* observer) {
	observers.push_back(observer); 
} 

void SimulationController::detach(IObserver* observer) {
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end()); 
} 

void SimulationController::notify(const TelemetryData& data) {
	for (auto* obs : observers) {
		obs->update(data); // or update(data) depending on your IObserver 
	} 
}
	
	
