#ifndef SIMPLECARDRAWER_H
#define SIMPLECARDRAWER_H

#include "ElementDrawer.h"

#include <vector>
class CarElement {
public:
	unsigned int shaderProgram;
	//unsigned int texture;
	unsigned int VAO;
	unsigned int viewLocation;
	unsigned int projectionLocation;
	unsigned int modelLocation;
	size_t indicesNumber;
	CarElement() :
		VAO(0),
		viewLocation(0),
		projectionLocation(0),
		modelLocation(0),
		indicesNumber(0) {};
};

class SimpleCarDrawer : public ElementDrawer {
private:
	std::vector<CarElement> elements;

public:
	SimpleCarDrawer(std::vector<CarElement> elements);

	void draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection) override;
};


#endif