#include "glad/glad.h"
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class SimpleScenarioDrawer {
public:
	void draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
	SimpleScenarioDrawer(unsigned int shaderProgram, unsigned int texture, unsigned int VAO, unsigned int viewLocation, unsigned int projectionLocation, unsigned int modelLocation);

private:
	unsigned int shaderProgram;
	unsigned int texture;
	unsigned int VAO;
	unsigned int viewLocation;
	unsigned int projectionLocation;
	unsigned int modelLocation;
};