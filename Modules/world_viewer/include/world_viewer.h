#ifndef WORLDVIEWER_H
#define WORLDVIEWER_H


#include "SimulatedWorld.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <thread>

class WorldViewer {
private:
	simulation::SimulatedWorld* world;
	GLFWwindow* window;

	int shaderProgram	=	0;
	unsigned int VAO	=	0;
	unsigned int VBO	=	0;
	unsigned int EBO	=	0;

	const char* vertexPath = "D:\\WorkSpace\\MCSuperCar\\Modules\\world_viewer\\graphic\\shaders\\vertexShader.txt";
	const char* fragmentPath = "D:\\WorkSpace\\MCSuperCar\\Modules\\world_viewer\\graphic\\shaders\\fragmentShader.txt";

	unsigned int texture1;
	unsigned int texture2;

public:
	WorldViewer(simulation::SimulatedWorld* world);
	~WorldViewer();
	void operator()();

	int setupWindow();
	void processInput();

	void BuildAndCompileShaderProgramTriangle();
	void setUPVertexAttributes();
	void createTexture();
	void deallocateResources();

	void getOpenGLInfo();
};

#endif