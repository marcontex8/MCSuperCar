#include "glad/glad.h"
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Drawer.h"

class SimpleTerrainDrawer : public Drawer {
public:
	void draw(glm::vec3 position, glm::quat orientation, Scene& scene);
	SimpleTerrainDrawer(unsigned int shaderProgram, unsigned int texture, unsigned int VAO, unsigned int viewLocation, unsigned int projectionLocation, unsigned int modelLocation);

private:
	unsigned int shaderProgram;
	unsigned int texture;
	unsigned int VAO;
	unsigned int viewLocation;
	unsigned int projectionLocation;
	unsigned int modelLocation;
};