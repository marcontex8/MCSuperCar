#ifndef VIEWERMANAGER_H
#define VIEWERMANAGER_H

#include "SimulatedWorld.h"
#include "worldViewer.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <future>

class WorldViewerManager {
private:
	simulation::SimulatedWorld* world;
public:
	std::atomic<bool> terminationFlag = false;
	std::future<bool> terminationResult;
	WorldViewerManager(simulation::SimulatedWorld* world);
	~WorldViewerManager();
	void initializeWorldView();
	void terminateWorldView();
};


#endif