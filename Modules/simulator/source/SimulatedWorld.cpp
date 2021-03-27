#include "SimulatedWorld.h"
#include<iostream>
#include "Diagnostics.h"
#include <chrono>
#include <SimulationElement_Car.h>

using namespace simulation;

extern Diagnostics diagnostics;

int SimulatedWorld::addElement(SimulationElement&& element) {
	std::unique_lock<std::shared_mutex> lk(elementsVectorMutex);
	std::cout << "addElement: " << typeid(element).name() << std::endl;
	SimulationElement* newElement;
	if (typeid(element) == typeid(SimulationElement_Car)) {
		newElement = new SimulationElement_Car(dynamic_cast<SimulationElement_Car&&>(element));
	}
	else {
		newElement = new SimulationElement(element);
	}
	elements.push_back(newElement);
	diagnostics.log("SimulatedWorld::addElement", Diagnostics::Topic::Simulation, Diagnostics::Verbosity::Debug);
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
