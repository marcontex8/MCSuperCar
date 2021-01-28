#include "ViewerManager.h"

#include<iostream>

ViewerManager::ViewerManager(simulation::SimulatedWorld* world):world(world) {
}

void ViewerManager::initializeWorldView() {
	WorldViewer worldViewer(world);
	std::thread viewerThread(worldViewer);
	viewerThread.detach();
}

ViewerManager::~ViewerManager() {
}
