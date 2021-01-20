#ifndef ELEMENTDRAWER_H
#define ELEMENTDRAWER_H

#include "glad/glad.h"
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ElementOpenGLDefinitions.h"

class ElementDrawer {
protected:
    ElementOpenGLDefinitions* openglElements;

    int modelLoc;
    int viewLoc;
    int projectionLoc;

public:
    ElementDrawer(ElementOpenGLDefinitions* openGLDefinitions);
    virtual ~ElementDrawer();
    void draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
};


#endif