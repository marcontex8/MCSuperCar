#ifndef DRAWER_H
#define DRAWER_H

#include "glad/glad.h"
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Drawer {
public:
    virtual ~Drawer() {};
    virtual void draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection) = 0;
};


#endif