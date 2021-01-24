#ifndef SIMULATIONELEMENTTRIANGLE_H
#define SIMULATIONELEMENTTRIANGLE_H

#include "SimulationElement.h"

namespace simulation {
	class SimulationElementTriangle : public SimulationElement {
	protected:
		double sideSize;

	public:
		SimulationElementTriangle();

		SimulationElementTriangle(
			int id,
			std::string name,
			double sideSize,
			Eigen::Vector3d position,
			Eigen::Quaterniond quaternion,
			double mass);
	};

}


#endif
