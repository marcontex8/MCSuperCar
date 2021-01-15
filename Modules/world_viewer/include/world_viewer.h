#ifndef WORLDVIEWER_H
#define WORLDVIEWER_H


#include "SimulatedWorld.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <thread>

// GLM
#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

class WorldViewer {
private:
	simulation::SimulatedWorld* world;
	GLFWwindow* window;

public:
	WorldViewer(simulation::SimulatedWorld* world);
	~WorldViewer();
	void operator()();

	int setupWindow();
	void processInput();

	void getOpenGLInfo();
};







#endif