#include "SimulationElement.h"
#include <iostream>
using namespace simulation;

SimulationElement::SimulationElement():
	x(0),
	y(0),
	z(0),
	mass(10),
	radius(1){
	name = "Element_" + std::to_string(elements_id++);
	std::cout << name << std::endl;
}