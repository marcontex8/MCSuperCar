#ifndef ELEMENTDRAWER_H
#define ELEMENTDRAWER_H

#include "glad/glad.h"
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ElementDrawer {
public:
    virtual ~ElementDrawer() {};
    virtual void draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection) = 0;
};


#endif