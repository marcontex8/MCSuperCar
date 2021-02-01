#include "ViewerManager.h"

#include<iostream>

ViewerManager::ViewerManager(simulation::SimulatedWorld* world):world(world) {
}

void ViewerManager::initializeWorldView() {
	std::thread viewerThread(
		[this]() {
			std::promise<bool> promise;
			this->terminationResult = promise.get_future();
			{
				WorldViewer worldViewer(&terminationFlag, world);
				worldViewer.runView();
			}
			promise.set_value(true);
			std::cout << "Viewer thread terminating." << std::endl;
		}
	);
	viewerThread.detach();
}

ViewerManager::~ViewerManager() {
	std::cout << "Viewer Manager destructor called." << std::endl;
	terminationFlag = true;
	try {
		terminationResult.wait();
		if (terminationResult.get()) {
			std::cout << "Viewer thread termiated correctly." << std::endl;
		}
	}
	catch (std::future_error e) {
		std::cout << "Vuewer thread termination incorrect." << std::endl;

	}
}
