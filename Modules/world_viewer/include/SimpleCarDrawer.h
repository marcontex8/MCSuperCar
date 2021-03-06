#ifndef SIMPLECARDRAWER_H
#define SIMPLECARDRAWER_H

#include "ElementDrawer.h"

#include <vector>
class CarElement {
public:
	unsigned int shaderProgram;
	unsigned int VAO;

	//uniforms locations
	unsigned int modelLocation;
	unsigned int viewLocation;
	unsigned int projectionLocation;

	unsigned int mat_diffuseLocation;
	unsigned int mat_specularLocation;
	unsigned int mat_shininessLocation;
	unsigned int mat_opacityLocation;

	unsigned int light_positionLocation;
	unsigned int light_ambientLocation;
	unsigned int light_diffuseLocation;
	unsigned int light_specularLocation;

	unsigned int viewPosLocation;

	// texture
	unsigned int texture_diffuse;
	unsigned int texture_specular;
	// light data
	glm::vec3 light_ambient;
	glm::vec3 light_diffuse;
	glm::vec3 light_specular;
	
	// material data
	float mat_opacity;
	float mat_shininess;

	size_t indicesNumber;
	CarElement() {};
};

class SimpleCarDrawer : public ElementDrawer {
private:
	std::vector<CarElement> elements;

public:
	SimpleCarDrawer(std::vector<CarElement> elements);

	void draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection) override;
};


#endif