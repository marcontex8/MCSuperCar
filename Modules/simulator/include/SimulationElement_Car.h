#ifndef SIMULATIONELEMENTCAR_H
#define SIMULATIONELEMENTCAR_H

#include "SimulationElement.h"

namespace simulation {
	enum class CarModels {
		Hatchback,
		Minivan,
		Sport,
		SUV
	};

	class SimulationElement_Car : public SimulationElement {
	public:
		SimulationElement_Car(int id, CarModels model = CarModels::SUV);
		void setSteering(float value);
		void setAcceleration(float value);
		const CarModels model;

	private:
		float steering;
		float acceleration;
	};
}

#endif