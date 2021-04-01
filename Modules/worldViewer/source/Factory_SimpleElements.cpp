#include "Factory_SimpleElements.h"
#include <iostream>
//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



#include "Diagnostics.h"

extern Diagnostics diagnostics;


unsigned int Textures::generateTexture(const char* texturePath) {
	unsigned int texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load and generate the texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	return texture;
}

void Vertices::setUpTexturedVertices(const float* verticesArray, const size_t size, unsigned int& VBO, unsigned int& VAO) {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(verticesArray), verticesArray, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}


void Vertices::setUpVertices(const float* verticesArray, const size_t size, unsigned int& VAO) {
	glGenVertexArrays(1, &VAO);
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(verticesArray), verticesArray, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void SimpleElementsFactory::setupBox() {
	box_shaderProgram = shaders->getBoxShader();
	box_texture = Textures::generateTexture(textures.boxTexturePath);
	Vertices::setUpTexturedVertices(Vertices::cubeTexturedVertices, Vertices::cubeTexturedSize, box_VBO, box_VAO);
	glUseProgram(box_shaderProgram);
	box_modelLoc = glGetUniformLocation(box_shaderProgram, "model");
	box_viewLoc = glGetUniformLocation(box_shaderProgram, "view");
	box_projectionLoc = glGetUniformLocation(box_shaderProgram, "projection");
}

BoxDrawer* SimpleElementsFactory::newBoxDrawer() {
	return new BoxDrawer(box_shaderProgram, box_texture, box_VAO, box_viewLoc, box_projectionLoc, box_modelLoc);
}

SimpleTerrainDrawer* SimpleElementsFactory::newSimpleTerrainDrawer() {
	return new SimpleTerrainDrawer(simpleScenario_shaderProgram, simpleScenario_texture, simpleScenario_VAO, simpleScenario_viewLoc, simpleScenario_projectionLoc, simpleScenario_modelLoc);
}


void SimpleElementsFactory::setupSimpleScenario() {
	simpleScenario_shaderProgram = shaders->getSimpleScenarioShader();
	Vertices::setUpVertices(Vertices::simpleScenarioVertices, Vertices::simpleScenarioSize, simpleScenario_VAO);
	glUseProgram(simpleScenario_shaderProgram);
	simpleScenario_modelLoc = glGetUniformLocation(simpleScenario_shaderProgram, "model");
	simpleScenario_viewLoc = glGetUniformLocation(simpleScenario_shaderProgram, "view");
	simpleScenario_projectionLoc = glGetUniformLocation(simpleScenario_shaderProgram, "projection");
}


SimpleElementsFactory::SimpleElementsFactory(Shaders* shaders):shaders(shaders) {
	setupBox();
	setupSimpleScenario();
}

SimpleElementsFactory::~SimpleElementsFactory() {
	glDeleteProgram(box_shaderProgram);
	glDeleteTextures(1, &box_texture);
	glDeleteVertexArrays(1, &box_VAO);
	glDeleteBuffers(1, &box_VBO);

	glDeleteProgram(simpleScenario_shaderProgram);
	glDeleteTextures(1, &simpleScenario_texture);
	glDeleteVertexArrays(1, &simpleScenario_VAO);
}