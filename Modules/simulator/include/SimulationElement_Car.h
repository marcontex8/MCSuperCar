#ifndef SIMULATIONELEMENTCAR_H
#define SIMULATIONELEMENTCAR_H

#include "SimulationElement.h"
#include <map>

namespace simulation {
	enum class CarModels {
		Hatchback,
		Minivan,
		Sport,
		SUV
	};

	struct CarProperties {
		double interaxisLenght;
		double maxAcceleration;
		double maxSeeringAngleDeg;
	};

	class SimulationElement_Car : public SimulationElement {
	public:
		SimulationElement_Car(int id, CarModels model = CarModels::SUV);
		void setSteering(double value);
		void setAcceleratorPedal(double value);
		const CarModels model;
		void update(unsigned long newTime);
		
		const double interaxisLenght;
		const double maxAcceleration;
		const double maxSeeringAngleDeg;
	private:
		// Inputs of the model
		double steering = 0;
		double acceleratorPedal = 0;

		// State of the model
		double velocityX = 0;
		double velocityY = 0;
		double alpha = 0;
		double positionX = 0;
		double positionY = 0;
	};
}

#endif