#ifndef WORLDVIEWER_H
#define WORLDVIEWER_H


#include "SimulatedWorld.h"

#include <map>
#include "ElementDrawer.h"

// OpenGL Libraries
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <thread>

// GLM
#include <glm/glm.hpp>

class WorldViewer {
private:
	simulation::SimulatedWorld* world;
	GLFWwindow* window;
	std::vector<ElementDrawer*> elementsReferences;

public:
	WorldViewer(simulation::SimulatedWorld* world);
	~WorldViewer();
	void operator()();

	int setupWindow();
	void processInput();

	void getOpenGLInfo();
};







#endif