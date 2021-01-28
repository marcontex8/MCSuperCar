#ifndef BOXDRAWER_H
#define BOXDRAWER_H
#include "ElementDrawer.h"

class BoxDrawer : public ElementDrawer {
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