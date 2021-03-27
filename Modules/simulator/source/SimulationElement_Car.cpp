#include "Diagnostics.h"
#include "SimulationElement_Car.h"

extern Diagnostics diagnostics;

namespace simulation {

	SimulationElement_Car::SimulationElement_Car(int id, CarModels model) :
		SimulationElement(id, "Car",Eigen::Vector3d(0, 0, 0), Eigen::Quaterniond(1,0,0,0), 1000),
		model(model),
		steering(0.0f),
		acceleration(0.0f)
	{
		diagnostics.log("Created SimulationElement_Car");
	}


	void SimulationElement_Car::setSteering(float value) {
		if (value < -1) {
			value = -1;
		}
		if (value > 1) {
			value = 1;
		}
		this->steering = value;
	}
	void SimulationElement_Car::setAcceleration(float value) {
		if (value < -1) {
			value = -1;
		}
		if (value > 1) {
			value = 1;
		}
		this->acceleration = value;
	}


}