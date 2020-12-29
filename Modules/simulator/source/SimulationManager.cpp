#include "SimulationManager.h"

#include<iostream>
#include<algorithm>
#include<chrono>

#include "Logger.h"


using namespace simulation;

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
		//simulationLogger->log("delay for "+std::to_string(delay.count()));
		std::this_thread::sleep_for(delay);
		//TODO: deal with the overtime elaboration!
	}
}

void SimulationManager::simulatePhysic(SimulationElement& element){
	int milliseconds = 20;
	element.x += (double)milliseconds / 1000 * 10;
	element.z += (double)milliseconds / 1000 * 5;
	element.y += (double)milliseconds / 1000 * 2;
	/*
	simulationLogger->log("Element in (" +
		std::to_string(element.x) +
		", " +
		std::to_string(element.y) +
		", " +
		std::to_string(element.x) +
		")");
		*/
}

