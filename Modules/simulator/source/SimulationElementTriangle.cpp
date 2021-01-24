#include "SimulationElementTriangle.h"

#include<iostream>



namespace simulation {

	SimulationElementTriangle::SimulationElementTriangle() : SimulationElement(), sideSize(1) {
		std::cout << "New generic Triangle Element created." << std::endl;
	}

	SimulationElementTriangle::SimulationElementTriangle(
		int id,
		std::string name,
		double sideSize,
		Eigen::Vector3d position,
		Eigen::Quaterniond orientation,
		double mass)
		:
		SimulationElement(id, name, position, orientation, mass),
		sideSize(sideSize) {
		
		std::cout << "Type Triangle, sideSize = " << sideSize << std::endl;

	}

}