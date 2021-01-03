#include "SimulatedWorld.h"
#include<iostream>

using namespace simulation;

int SimulatedWorld::addElement(SimulationElement&& element) {
	std::lock_guard<std::mutex> guard(dataMutex);
	elements.push_back(element);
	std::cout << "SimulatedWorld::addElement" << std::endl;
	return 1;
};

int SimulatedWorld::numberOfElements() {
	std::lock_guard<std::mutex> guard(dataMutex);
	return elements.size();
}

int SimulatedWorld::getElementAtIndex(int index, SimulationElement* elementOut) {
	std::lock_guard<std::mutex> guard(dataMutex);
	//std::cout << "SimulatedWorld | Required index " << index << std::endl;
	if (index > elements.size()) {
		return 0;
	}
	else
	{
		*elementOut = elements[index];
		return index;
	}
}



void SimulatedWorld::doSomething() {
	std::cout << "Ciao!" << std::endl;
}