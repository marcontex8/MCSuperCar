#ifndef WORLDVIEWER_H
#define WORLDVIEWER_H

#include <exception>

#include "SimulatedWorld.h"

#include "Drawer.h"
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
	std::vector<Drawer*> elementsReferences;
	std::atomic<bool>* terminationFlag;
	int window_height = 1200;
	int window_width = 1200;

public:
	class WindowGenerationException : public std::exception {};
	class GladInitializationException : public std::exception {};

	WorldViewer(std::atomic<bool>* terminationFlag, simulation::SimulatedWorld* world);
	~WorldViewer();
	void runView();

	void setupWindow();
	void processInput();

	void getOpenGLInfo();
};







#endif