#include "SimulatedWorld.h"
#include<iostream>
#include "Diagnostics.h"
#include <chrono>
#include <SimulationElement_Car.h>

using namespace simulation;

extern Diagnostics diagnostics;

int SimulatedWorld::addElement(SimulationElement&& element) {
	std::unique_lock<std::shared_mutex> lk(elementsVectorMutex);
	SimulationElement* newElement;
	if (typeid(element) == typeid(SimulationElement_Car)) {
		newElement = new SimulationElement_Car(dynamic_cast<SimulationElement_Car&&>(element));
	}
	else {
		newElement = new SimulationElement(element);
	}
	newElement->setTime(this->simulationTime);
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
	diagnostics.log("Required element at index "+std::to_string(index), Diagnostics::Topic::Simulation, Diagnostics::Verbosity::Debug);
	if (index <= 0 || index > elements.size()) {
		return nullptr;
	}
	else
	{
		return elements[index];
	}
}


void SimulatedWorld::performTimeStep(unsigned int timeStep) {
	this->simulationTime += timeStep;
	std::unique_lock<std::shared_mutex> lk(elementsVectorMutex);
	for (auto it = elements.begin(); it != elements.end(); ++it) {
		(*it)->update(this->simulationTime);
	}

	// check for collisions

	// set inputs
}
