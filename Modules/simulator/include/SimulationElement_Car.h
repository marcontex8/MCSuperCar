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
		void setSteering(double value);
		void setAcceleratorPedal(double value);
		const CarModels model;
		void update(unsigned long newTime);
		
		const double interaxisLenght = 3.0;
		const double maxSeeringAngleDeg = 45;
		const double maxAcceleration = 2.7;
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