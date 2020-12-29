#ifndef SIMULATEDWORLD_H
#define SIMULATEDWORLD_H

#include<vector>
#include<mutex>


#include "SimulationElement.h"

namespace simulation {

	class SimulatedWorld
	{
	private:
		std::vector<SimulationElement> elements;
		std::mutex dataMutex;

	public:
		int addElement(SimulationElement element);
		void doSomething();

		template<typename F> void applyToElements(F elaboration) {
			std::lock_guard<std::mutex> guard(dataMutex);
			for (auto it = elements.begin(); it != elements.end(); ++it) {
				elaboration(*it);
			}
		}
	};
}


#endif