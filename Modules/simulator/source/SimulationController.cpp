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
	return pauseRequired;
};

bool SimulationController::isStopRequired() {
	std::lock_guard<std::mutex> guard(dataMutex);
	return stopRequired;
};

void SimulationController::requirePause(bool require) {
	std::lock_guard<std::mutex> guard(dataMutex);
	pauseRequired = require;
};

void SimulationController::requireStop(bool require) {
	std::lock_guard<std::mutex> guard(dataMutex);
	stopRequired = require;
};

void SimulationController::setPause(bool value) {
	std::lock_guard<std::mutex> guard(dataMutex);
	pause = value;
};

void SimulationController::setStop(bool value) {
	std::lock_guard<std::mutex> guard(dataMutex);
	stop = value;
};

bool SimulationController::getPause() {
	std::lock_guard<std::mutex> guard(dataMutex);
	return pause;
};

bool SimulationController::getStop() {
	std::lock_guard<std::mutex> guard(dataMutex);
	return pause;
};