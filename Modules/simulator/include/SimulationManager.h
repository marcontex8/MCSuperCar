#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H


#include<thread>

#include "Logger.h"
#include "SimulationElement.h"
#include "SimulatedWorld.h"
#include "SimulationController.h"

namespace simulation{

	class SimulationManager
	{
	public:
		SimulatedWorld* simulatedWorld;
		SimulationController simulationController;

		SimulationManager(SimulatedWorld* simulatedWorld);
		
		void beginSimulation();
		void endSimulation();

		void playSimulation();
		void pauseSimulation();

		bool simulationEnded();

	private:
		std::thread simulation_thread;
		static void simulate(SimulatedWorld* world, SimulationController* controller);
		static void simulatePhysic(SimulationElement& element);
	};




}

#endif