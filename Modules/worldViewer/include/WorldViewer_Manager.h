#ifndef VIEWERMANAGER_H
#define VIEWERMANAGER_H

#include "SimulatedWorld.h"
#include "worldViewer.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <future>

class WorldViewerManager {
private:
	std::shared_ptr<simulation::SimulatedWorld> world;
public:
	std::atomic<bool> terminationFlag = false;
	std::future<bool> terminationResult;
	WorldViewerManager(std::shared_ptr<simulation::SimulatedWorld>& simulatedWorld);
	~WorldViewerManager();
	void initializeWorldView();
	void terminateWorldView();
};


#endif