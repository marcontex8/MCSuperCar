#ifndef DRAWER_BOX_H
#define DRAWER_BOX_H
#include "Drawer.h"

class BoxDrawer : public Drawer {
private:
	unsigned int shaderProgram;
	unsigned int texture;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int viewLocation;
	unsigned int projectionLocation;
	unsigned int modelLocation;

public:
	BoxDrawer(unsigned int shaderProgram, unsigned int texture, unsigned int VAO, unsigned int VBO, unsigned int viewLocation, unsigned int projectionLocation, unsigned int modelLocation);

	void draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection) override;
};


#endif