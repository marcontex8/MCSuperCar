#include "SimulationElement.h"
#include <iostream>
using namespace simulation;

SimulationElement::SimulationElement():
	x((double)elements_id/100),
	y((double)elements_id/100),
	z((double)elements_id/100),
	mass(10),
	radius(1){
	name = "Element_" + std::to_string(elements_id++);
	std::cout << name << std::endl;
}