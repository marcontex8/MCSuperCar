#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H


#include<thread>

#include "Diagnostics.h"
#include "SimulationElement.h"
#include "SimulationElement_Car.h"
#include "SimulatedWorld.h"
#include "SimulationController.h"

namespace simulation{

	class SimulationManager
	{
	public:
		std::shared_ptr<SimulatedWorld> simulatedWorld;
		SimulationController simulationController;

		SimulationManager(std::shared_ptr<SimulatedWorld>& simulatedWorld);
		
		void beginSimulation();
		void endSimulation();

		void playSimulation();
		void pauseSimulation();

		bool simulationEnded();

	private:
		std::thread simulation_thread;
		static void simulate(std::shared_ptr<SimulatedWorld> world, SimulationController* controller);
	};




}

#endif