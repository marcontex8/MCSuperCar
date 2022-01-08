#ifndef SIMULATIONCONTROLLER_H
#define SIMULATIONCONTROLLER_H

#include<mutex>
#include <condition_variable>

namespace simulation {

	class SimulationController
	{
	private:
		std::atomic<int> simulationInterval = 20;
		std::atomic<bool> pauseRequired	= true;
		std::atomic<bool> stopRequired	= true;
		std::atomic<bool> pause	= true;
		std::atomic<bool> stop	= true;


	public:
		SimulationController() = default;

		int setSimulationIntervalMillis(int interval);
		int getSimulationIntervalMillis();

		bool isPauseRequired();
		bool isStopRequired();

		void requirePause(bool require);
		void requireStop(bool require);

		void setPause(bool value);
		void setStop(bool value);

		bool getPause();
		bool getStop();

	};

}


#endif