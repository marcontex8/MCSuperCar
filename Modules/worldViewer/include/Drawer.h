#ifndef DRAWER_H
#define DRAWER_H

#include "glad/glad.h"
// GLM
#include <glm/glm.hpp>

#include "Scene.h"

class Drawer {
public:
    virtual ~Drawer() {};
    virtual void draw(glm::vec3 position, glm::quat orientation, Scene& scene) = 0;
};


#endif