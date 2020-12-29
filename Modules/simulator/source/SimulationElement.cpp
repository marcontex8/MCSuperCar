#include "SimulationElement.h"

using namespace simulation;

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