#ifndef SIMULATIONCONTROLLER_H
#define SIMULATIONCONTROLLER_H

#include<mutex>
#include <condition_variable>

namespace simulation {

	class SimulationController
	{
	private:
		int simulationInterval = 20;
		bool pauseRequired	= true;
		bool stopRequired	= true;
		bool pause	= true;
		bool stop	= true;


		std::mutex dataMutex;


	public:
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