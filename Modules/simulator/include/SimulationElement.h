#ifndef SIMULATIONELEMENT_H
#define SIMULATIONELEMENT_H

#include <string>
static int elements_id = 0;

namespace simulation {
	class SimulationElement {
	public:
		SimulationElement();
		std::string name;
		double x;
		double y;
		double z;
		double mass;
		double radius;
	};
}


#endif