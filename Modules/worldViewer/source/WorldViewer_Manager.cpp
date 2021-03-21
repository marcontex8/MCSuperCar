#include "WorldViewer_Manager.h"

#include<iostream>

WorldViewerManager::WorldViewerManager(simulation::SimulatedWorld* world):world(world) {
}

void WorldViewerManager::initializeWorldView() {
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

WorldViewerManager::~WorldViewerManager() {
	std::cout << "Viewer Manager destructor called." << std::endl;
	terminationFlag = true;
	try {
		terminationResult.wait();
		if (terminationResult.get()) {
			std::cout << "Viewer thread termiated correctly." << std::endl;
		}
	}
	catch (std::future_error e) {
		std::cout << "Viewer thread termination incorrect." << std::endl;

	}
}
