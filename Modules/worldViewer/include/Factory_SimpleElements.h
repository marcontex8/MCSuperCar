#ifndef OPENGLDEFINITIONSFACTORY_H
#define OPENGLDEFINITIONSFACTORY_H

#include "Drawer.h"
#include "Drawer_Box.h"
#include "Drawer_SimpleTerrain.h"
#include "Shaders.h"

class Textures {
public:
	const char* boxTexturePath = R"(D:\WorkSpace\MCSuperCar\Modules\worldViewer\graphic\container.jpg)";
	const char* simpleScenarioTexturePath = R"(D:\WorkSpace\MCSuperCar\Modules\worldViewer\graphic\asphalt.jpg)";

	static unsigned int generateTexture(const char* texturePath);
};


class Vertices {
public:
	static constexpr size_t cubeTexturedSize = 5 * 6 * 6;
	static constexpr float cubeTexturedVertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	static constexpr size_t simpleScenarioSize = 3*6;
	static constexpr float simpleScenarioVertices[simpleScenarioSize] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f
	};

	static void Vertices::setUpTexturedVertices(const float* verticesArray, const size_t size, unsigned int& VBO, unsigned int& VAO);

	static void Vertices::setUpVertices(const float* verticesArray, const size_t size, unsigned int& VAO);

};


class SimpleElementsFactory {
private:
	Shaders* shaders;
	Textures textures;
	Vertices vertices;
	unsigned int box_VAO = 0;
	unsigned int box_VBO = 0;
	unsigned int box_shaderProgram = 0;
	unsigned int box_texture = 0;
	unsigned int box_modelLoc = 0;
	unsigned int box_viewLoc = 0;
	unsigned int box_projectionLoc = 0;

	unsigned int simpleScenario_VAO = 0;
	unsigned int simpleScenario_shaderProgram = 0;
	unsigned int simpleScenario_texture = 0;
	unsigned int simpleScenario_modelLoc = 0;
	unsigned int simpleScenario_viewLoc = 0;
	unsigned int simpleScenario_projectionLoc = 0;
	unsigned int simpleScenario_translationsLoc = 0;

public:
	SimpleElementsFactory(Shaders* shaders);
	~SimpleElementsFactory();
	void setupBox();
	void setupSimpleScenario();
	BoxDrawer* newBoxDrawer();
	SimpleTerrainDrawer* newSimpleTerrainDrawer();

};


#endif