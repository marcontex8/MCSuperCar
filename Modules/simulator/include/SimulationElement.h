#ifndef SIMULATIONELEMENT_H
#define SIMULATIONELEMENT_H


namespace simulation {
	class SimulationElement {
	public:
		SimulationElement();
		SimulationElement(const SimulationElement&);
		SimulationElement& operator=(const SimulationElement&);
		SimulationElement(SimulationElement&&) = default;
		double x;
		double y;
		double z;
		double mass;
		double radius;
	};
}


#endif