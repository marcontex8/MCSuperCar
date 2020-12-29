#include "SimulatedWorld.h"
#include<iostream>

using namespace simulation;

int SimulatedWorld::addElement(SimulationElement element) {
	std::lock_guard<std::mutex> guard(dataMutex);
	elements.push_back(element);
	return 1;
};

void SimulatedWorld::doSomething() {
	std::cout << "Ciao!" << std::endl;
}