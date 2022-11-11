#include "SimulationManager.h"

#include<iostream>
#include<algorithm>
#include<chrono>

#include "Diagnostics.h"


using namespace simulation;

extern Diagnostics diagnostics;

SimulationManager::SimulationManager(std::shared_ptr<SimulatedWorld>& simulatedWorld)
	:simulatedWorld{ simulatedWorld }, simulationController{} {
};


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

void SimulationManager::simulate(std::shared_ptr<SimulatedWorld> world, SimulationController* controller){
	diagnostics.log("beginning simulate function", Diagnostics::Topic::Simulation, Diagnostics::Verbosity::Debug);
	unsigned int loopCounter = 0;
	while(true){
		loopCounter++;
		diagnostics.monitor("SIMULATION LOOP", std::to_string(loopCounter));
		if (controller->isStopRequired()) {
			controller->setStop(true);
			diagnostics.monitor("status", "\tSTOP REQUIRED");
			break;
		}
		if (controller->isPauseRequired()) {
			controller->setPause(true);
			diagnostics.monitor("status", "\tPAUSE REQUIRED");
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			continue;
		}
		diagnostics.monitor("status", "\tRUNNING");
		auto start = std::chrono::high_resolution_clock::now();
		world->performTimeStep(controller->getSimulationIntervalMillis());

		auto stop = std::chrono::high_resolution_clock::now();
		auto delay = std::chrono::milliseconds(controller->getSimulationIntervalMillis()) - (stop - start);
		//simulationLogger->log("delay for "+std::to_string(delay.count()));
		static int number_of_overrunned_cycles = 0;
		if (delay.count() < 0) {
			number_of_overrunned_cycles++;
			continue;
		}
		if (number_of_overrunned_cycles > 3) {
			std::cerr << "ERROR: program over-runned for 3 cycles" << std::endl;
			diagnostics.log("ERROR: program over-runned for 3 cycles", Diagnostics::Topic::Simulation, Diagnostics::Verbosity::Error);

			return;
		}
		std::this_thread::sleep_for(delay);
	}
}
