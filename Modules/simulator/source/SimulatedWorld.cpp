#include "SimulatedWorld.h"
#include<iostream>

using namespace simulation;

int SimulatedWorld::addElement(SimulationElement&& element) {
	std::unique_lock<std::shared_mutex> lk(elementsVectorMutex);
	elements.push_back(new SimulationElement(element));
	std::cout << "SimulatedWorld::addElement" << std::endl;
	return 1;
};

int SimulatedWorld::numberOfElements() const {
	std::shared_lock<std::shared_mutex> lk(elementsVectorMutex);
	return (int)elements.size();
}

SimulationElement* SimulatedWorld::getElementAtIndex(int index) const {
	std::shared_lock<std::shared_mutex> lk(elementsVectorMutex);
	std::cout << "SimulatedWorld | Required index " << index << std::endl;
	if (index > elements.size()) {
		return nullptr;
	}
	else
	{
		return elements[index];
	}
}

void SimulatedWorld::doSomething() {
	std::cout << "Ciao!" << std::endl;
}