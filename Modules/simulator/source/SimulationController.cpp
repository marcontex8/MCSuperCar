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
	return pauseRequired;
};

bool SimulationController::isStopRequired() {
	return stopRequired;
};

void SimulationController::requirePause(bool require) {
	pauseRequired = require;
};

void SimulationController::requireStop(bool require) {
	stopRequired = require;
};

void SimulationController::setPause(bool value) {
	pause = value;
};

void SimulationController::setStop(bool value) {
	stop = value;
};

bool SimulationController::getPause() {
	return pause;
};

bool SimulationController::getStop() {
	return pause;
};