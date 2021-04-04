#ifndef DRAWER_CARPACK001_H
#define DRAWER_CARPACK001_H

#include "Drawer.h"

#include <vector>
class CarElement {
public:
	unsigned int shaderProgram = 0;
	unsigned int VAO = 0;

	//uniforms locations
	unsigned int modelLocation = 0;
	unsigned int viewLocation = 0;
	unsigned int projectionLocation = 0;

	unsigned int mat_diffuseLocation = 0;
	unsigned int mat_specularLocation = 0;
	unsigned int mat_shininessLocation = 0;
	unsigned int mat_opacityLocation = 0;

	unsigned int light_positionLocation = 0;
	unsigned int light_ambientLocation = 0;
	unsigned int light_diffuseLocation = 0;
	unsigned int light_specularLocation = 0;

	unsigned int viewPosLocation = 0;

	// textures
	unsigned int texture_diffuse = 0;
	unsigned int texture_specular = 0;

	// light data
	glm::vec3 light_ambient = {0.0f, 0.0f, 0.0f};
	glm::vec3 light_diffuse = { 0.0f, 0.0f, 0.0f };
	glm::vec3 light_specular = { 0.0f, 0.0f, 0.0f };
	
	// material data
	float mat_opacity = 0;
	float mat_shininess = 0;

	size_t indicesNumber = 0;
	CarElement() {};
};

class CarPack001Drawer : public Drawer {
private:
	std::vector<CarElement> elements;

public:
	CarPack001Drawer(std::vector<CarElement> elements);

	void draw(glm::vec3 position, glm::quat orientation, Scene& scene) override;
};


#endif