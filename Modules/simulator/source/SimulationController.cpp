#include "SimulationController.h"

using namespace simulation;

int SimulationController::setSimulationIntervalMillis(int interval) {
	this->simulationInterval = interval;
	return interval;
};

int SimulationController::getSimulationIntervalMillis() {
	return this->simulationInterval;
};


bool SimulationController::isPauseRequired() {
	std::lock_guard<std::mutex> guard(dataMutex);
	return pause;
};

bool SimulationController::isStopRequired() {
	std::lock_guard<std::mutex> guard(dataMutex);
	return stop;
};
void SimulationController::requirePause(bool require) {
	std::lock_guard<std::mutex> guard(dataMutex);
	pause = require;
};
void SimulationController::requireStop(bool require) {
	std::lock_guard<std::mutex> guard(dataMutex);
	stop = require;
};