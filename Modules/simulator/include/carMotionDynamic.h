#pragma once
#include "simulationSettings.h"
#include<vector>
namespace CarMotionDynamic{
	class Speed {
	public:
		double x;
		double y;
	};

	class Car
	{
	private:
		double mass;
		double force;
		unsigned int simulationTime;
		Speed speed;
	public:
		Car(double mass, double force);
		void startSimulation(unsigned int simulationTime);
		void stopSimulation();
	private:
		void update(unsigned int newSimulationTime);

	};
}

