#ifndef VIEWERMANAGER_H
#define VIEWERMANAGER_H

#include "SimulationManager.h"
#include "world_viewer.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class ViewerManager {
private:
	simulation::SimulatedWorld* world;

public:
	ViewerManager(simulation::SimulatedWorld* world);
	~ViewerManager();
	void initializeWorldView();
};


#endif