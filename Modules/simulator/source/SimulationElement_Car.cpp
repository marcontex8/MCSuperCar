#include "Diagnostics.h"
#include "SimulationElement_Car.h"

extern Diagnostics diagnostics;

namespace simulation {
	std::map<CarModels, CarProperties> carProperties = {
		std::pair{CarModels::Hatchback, CarProperties{3.0, 2.4, 40} },
		std::pair{CarModels::Minivan,	CarProperties{4.7, 2.7, 45} },
		std::pair{CarModels::Sport,		CarProperties{4.0, 7.0, 30} },
		std::pair{CarModels::SUV,		CarProperties{4.5, 4.0, 60} }
	};


	SimulationElement_Car::SimulationElement_Car(int id, CarModels model) :
		SimulationElement(id, "Car",Eigen::Vector3d(0, 0, 0), Eigen::Quaterniond(1,0,0,0), 1000),
		model(model),
		steering(0.0f),
		acceleratorPedal(0.0f),
		interaxisLenght(carProperties[model].interaxisLenght),
		maxAcceleration(carProperties[model].maxAcceleration),
		maxSeeringAngleDeg(carProperties[model].maxSeeringAngleDeg)
	{
		diagnostics.log("Created SimulationElement_Car");
	}


	void SimulationElement_Car::setSteering(double value) {
		if (value < -1) {
			value = -1;
		}
		if (value > 1) {
			value = 1;
		}
		this->steering = value;
	}
	void SimulationElement_Car::setAcceleratorPedal(double value) {
		if (value < -1) {
			value = -1;
		}
		if (value > 1) {
			value = 1;
		}
		this->acceleratorPedal = value;
	}

	void SimulationElement_Car::update(unsigned long newTime) {
		double delta = (static_cast<double>(newTime) - static_cast<double>(this->simulationTime))/1000;
		this->simulationTime = newTime;
		diagnostics.monitor("delta", std::to_string(delta));

		// generate physical inputs according to UI inputs and car physical model
		double accelerationModule = maxAcceleration * acceleratorPedal;
		double steeringAngle = maxSeeringAngleDeg * steering /360 * 2 * 3.14;

		diagnostics.monitor(std::string("accelerationModule ") + std::to_string(this->id), std::to_string(accelerationModule));
		diagnostics.monitor(std::string("steeringAngle ")      + std::to_string(this->id), std::to_string(steeringAngle));

		double velocityModule = sqrt(pow(velocityX, 2) + pow(velocityY, 2));
		velocityX = (velocityModule + accelerationModule * delta) * sin(alpha + steeringAngle);
		velocityY = (velocityModule + accelerationModule * delta) * cos(alpha + steeringAngle);
		alpha	  += velocityModule / interaxisLenght * sin(steeringAngle) * delta;

		positionX += velocityX * delta;
		positionY += velocityY * delta;

		diagnostics.monitor(std::string("velocityX ") + std::to_string(this->id), std::to_string(velocityX));
		diagnostics.monitor(std::string("velocityY ") + std::to_string(this->id), std::to_string(velocityY));
		diagnostics.monitor(std::string("alpha ")     + std::to_string(this->id), std::to_string(alpha));


		setPosition(positionX, positionY, 0.0);
		setOrientation(Eigen::Quaterniond(Eigen::AngleAxisd(alpha + 3.14, Eigen::Vector3d(0.0, 0.0, -1.0) ) ) );
	}

}