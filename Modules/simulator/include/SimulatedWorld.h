#ifndef SIMULATEDWORLD_H
#define SIMULATEDWORLD_H

#include<vector>
#include<shared_mutex>


#include "SimulationElement.h"

namespace simulation {

	class SimulatedWorld
	{
	private:
		std::vector<SimulationElement*> elements;
		mutable std::shared_mutex elementsVectorMutex;
		unsigned long simulationTime = 0;
	public:
		int addElement(SimulationElement&& element);
		int numberOfElements() const;
		SimulationElement* getElementAtIndex(int index) const;

		template<typename F> void applyToElements(F elaboration) {
			std::shared_lock<std::shared_mutex> lk(elementsVectorMutex);
			int i = 0;
			for (auto it = elements.begin(); it != elements.end(); ++it) {
				elaboration(*it);
			}
		}

		void performTimeStep(unsigned int timeStep);
	};
}


#endif