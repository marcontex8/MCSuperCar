#pragma once

#include<vector>
#include<thread>
#include<chrono>
#include<mutex>

namespace simulation{
	class SimulationElement;
	class SimulationManager;
	class SimulationController;
	class SimulatedWorld;

	class SimulatedWorld
	{
	private:
		std::vector<SimulationElement> elements;
		std::mutex dataMutex;

	public:
		int addElement(SimulationElement element);
		template<typename F> void applyToElements(F elaboration);
	};

	class SimulationController
	{
	private:
		int simulationInterval	=	20;
		bool pause	=	true;
		bool stop	=	false;
		std::mutex dataMutex;
	public:
		int setSimulationIntervalMillis(int interval);
		int getSimulationIntervalMillis();

		bool isPauseRequired();
		bool isStopRequired();
		void requirePause(bool require);
		void requireStop(bool require);
	};

	class SimulationManager
	{
	public:
		SimulationManager(SimulatedWorld* simulatedWorld);
		SimulatedWorld* simulatedWorld;
		SimulationController simulationController;

		void beginSimulation();
		void endSimulation();

		void playSimulation();
		void pauseSimulation();

		bool simulationEnded();

	private:
		std::thread simulation_thread;
		static void simulate(SimulatedWorld* simulatedWorld, SimulationController* simulationController);
		static void simulatePhysic(SimulationElement& element);
	};


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