#include "SimulationManager.h"
#include "Logger.h"
#include<iostream>
#include<algorithm>

extern Logger simulationLogger;

using namespace simulation;

int SimulatedWorld::addElement(SimulationElement element) {
	std::lock_guard<std::mutex> guard(dataMutex);
	elements.push_back(element);
	return 1;
};

template<typename F> void SimulatedWorld::applyToElements(F elaboration) {
	for (auto it = elements.begin(); it != elements.end(); ++it) {
		elaboration(*it);
	}
}

int SimulationController::setSimulationIntervalMillis(int interval) {
	this->simulationInterval = interval;
	return interval;
};

int SimulationController::getSimulationIntervalMillis() {
	return this->simulationInterval;
}


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

SimulationManager::SimulationManager(SimulatedWorld* simulatedWorld)
	:simulatedWorld(simulatedWorld) {};


void SimulationManager::beginSimulation() {
	simulationController.requireStop(false);
	simulationController.requirePause(false);
	simulation_thread = std::thread(SimulationManager::simulate, simulatedWorld, &simulationController);
	simulation_thread.detach();
}

void SimulationManager::endSimulation() {
	simulationController.requireStop(true);
	//Kill the simulation thread in some way from here?
};

void SimulationManager::playSimulation() {
	simulationController.requirePause(false);
};

void SimulationManager::pauseSimulation() {
	simulationController.requirePause(true);
};

bool SimulationManager::simulationEnded() {
	//TODO eliminare questo fafugnezzo
	static int counter = 0;
	if (counter == 100) {
		return true;
	}
	counter++;
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	return false;
}
void SimulationManager::simulate(SimulatedWorld* world, SimulationController* controller){
	std::cout << "beginning simulate function" << std::endl;
	while(true){
		if (controller->isPauseRequired()) {
			std::cout << "pause required, waiting 100ms" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			continue;
		}
		if (controller->isStopRequired()) {
			std::cout << "stop required" << std::endl;
			break;
		}
		auto start = std::chrono::high_resolution_clock::now();
		world->applyToElements(simulatePhysic);

		auto stop = std::chrono::high_resolution_clock::now();
		auto delay = std::chrono::milliseconds(controller->getSimulationIntervalMillis()) - (stop - start);
		simulationLogger.log("delay for "+std::to_string(delay.count()));
		std::this_thread::sleep_for(delay);
		//TODO: deal with the overtime elaboration!
	}
}

void SimulationManager::simulatePhysic(SimulationElement& element){
	int milliseconds = 20;
	element.x += (double)milliseconds / 1000 * 10;
	element.z += (double)milliseconds / 1000 * 5;
	element.y += (double)milliseconds / 1000 * 2;
	simulationLogger.log("Element in (" +
		std::to_string(element.x) +
		", " +
		std::to_string(element.y) +
		", " +
		std::to_string(element.x) +
		")");
}


SimulationElement::SimulationElement() {
	x = 0;
	y = 0;
	z = 0;
	mass = 10;
	radius = 1;
}

SimulationElement::SimulationElement(const SimulationElement& element2) {
	x = element2.x;
	y = element2.y;
	z = element2.z;
	mass = element2.mass;
	radius = element2.radius;
}

SimulationElement& SimulationElement::operator=(const SimulationElement& other) {
	return *this;
}