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
	simulationController.requirePause(true);
	simulationController.setStop(false);
	simulationController.setPause(false);
	simulation_thread = std::thread(SimulationManager::simulate, simulatedWorld, &simulationController);
	simulation_thread.detach();
}

void SimulationManager::endSimulation() {
	simulationController.requireStop(true);
	while (!simulationController.getStop()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
};

void SimulationManager::playSimulation() {
	simulationController.requirePause(false);
};

void SimulationManager::pauseSimulation() {
	simulationController.requirePause(true);
	while (!simulationController.getPause()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
};

void SimulationManager::simulate(SimulatedWorld* world, SimulationController* controller){
	std::cout << "SIMULATION | beginning simulate function" << std::endl;
	while(true){
		if (controller->isStopRequired()) {
			controller->setStop(true);
			std::cout << "SIMULATION | stop required, break" << std::endl;
			break;
		}
		if (controller->isPauseRequired()) {
			controller->setPause(true);
			std::cout << "SIMULATION | pause required, waiting 100ms" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			continue;
		}
		std::cout << "SIMULATION | simulation running." << std::endl;
		auto start = std::chrono::high_resolution_clock::now();
		world->applyToElements(simulatePhysic);

		auto stop = std::chrono::high_resolution_clock::now();
		auto delay = std::chrono::milliseconds(controller->getSimulationIntervalMillis()) - (stop - start);
		//simulationLogger->log("delay for "+std::to_string(delay.count()));
		std::this_thread::sleep_for(delay);
		static int number_of_overruned_cycles = 0;
		if (number_of_overruned_cycles > 3) {
			std::cerr << "ERROR: program over-runned for 3 cycles" << std::endl;
			return;
		}
	}
}

void SimulationManager::simulatePhysic(SimulationElement* element){
	int milliseconds = 20;
	element->setPosition(
		element->getPosition()[0] + (double)milliseconds / 10000 * cos((double)element->id / 5 * 2 * 3.14),
		element->getPosition()[1] + (double)milliseconds / 1000 * sin((double)element->id / 5 * 2 * 3.14),
		element->getPosition()[2]);
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

