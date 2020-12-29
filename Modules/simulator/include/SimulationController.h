#ifndef SIMULATIONCONTROLLER_H
#define SIMULATIONCONTROLLER_H

#include<mutex>

namespace simulation {

	class SimulationController
	{
	private:
		int simulationInterval = 20;
		bool pause = true;
		bool stop = false;
		std::mutex dataMutex;
	public:
		int setSimulationIntervalMillis(int interval);
		int getSimulationIntervalMillis();

		bool isPauseRequired();
		bool isStopRequired();
		void requirePause(bool require);
		void requireStop(bool require);
	};

}


#endif