#ifndef VIEWERMANAGER_H
#define VIEWERMANAGER_H

#include "SimulatedWorld.h"
#include "world_viewer.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <future>

class ViewerManager {
private:
	simulation::SimulatedWorld* world;
public:
	std::atomic<bool> terminationFlag = false;
	std::future<bool> terminationResult;
	ViewerManager(simulation::SimulatedWorld* world);
	~ViewerManager();
	void initializeWorldView();
};


#endif