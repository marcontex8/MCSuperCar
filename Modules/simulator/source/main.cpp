#include "SimulationManager.h"
#include "Logger.h"

#include <iostream>
#include <fstream>

using namespace simulation;
Logger simulationLogger;

int main(int argc, char* argv[]) {
	simulationLogger.initialize();
	SimulatedWorld world;
	SimulationElement element1;
	SimulationElement element2;
	SimulationElement element3;
	std::cout << "created elements" << std::endl;

	world.addElement(element1);
	world.addElement(element2);
	world.addElement(element3);
	std::cout << "added elements" << std::endl;

	SimulationManager simulationManager(&world);
	std::cout << "created manager" << std::endl;

	simulationManager.simulationController.setSimulationIntervalMillis(20);
	std::cout << "set interval" << std::endl;

	simulationManager.beginSimulation();
	std::cout << "simulation running" << std::endl;


	bool done = false;
	while (!done) {
		std::cout << "nuovo ciclo" << std::endl;
		std::string input;
		// user input
		std::getline(std::cin, input);
		std::cout << input << std::endl;
		if (input == "q") {
			
			std::cout << "Simulation End required." << std::endl;
			simulationManager.endSimulation();
			while (!simulationManager.simulationEnded()) {
				std::cout << "waiting for simulation to end..." << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
				continue;
			}
			done = true;
			input = "";
			break;
		}

		if (input == "p") {
			std::cout << "Simulation pause required." << std::endl;
			simulationManager.pauseSimulation();
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			input = "";
			continue;
		}

		if (input == "r") {
			std::cout << "Simulation play required." << std::endl;
			simulationManager.playSimulation();
			input = "";
			continue;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}