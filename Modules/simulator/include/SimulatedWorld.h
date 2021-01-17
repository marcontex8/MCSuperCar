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
	public:
		int addElement(SimulationElement&& element);
		int numberOfElements() const;
		SimulationElement* getElementAtIndex(int index) const;
		void doSomething();

		template<typename F> void applyToElements(F elaboration) {
			std::shared_lock<std::shared_mutex> lk(elementsVectorMutex);
			std::cout << "Called applyToElements() " << std::endl;
			int i = 0;
			for (auto it = elements.begin(); it != elements.end(); ++it) {
				std::cout << "i = " << i++ << std::endl;
				elaboration(*it);
			}
		}
	};
}


#endif