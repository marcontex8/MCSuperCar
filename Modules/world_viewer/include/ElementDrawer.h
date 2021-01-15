#ifndef ELEMENTDRAWER_H
#define ELEMENTDRAWER_H

#include "glad/glad.h"
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



class ElementDrawer {
protected:
    //paths and elements for drawing
    size_t verticesNumber;
    float* verticesArray;
    char* vertexShaderPath;
    char* fragmentShaderPath;
    char* texturePath;
    
    //OpenGL ids
    int shaderProgram = 0;
    unsigned int VAO = 0;
    unsigned int VBO = 0;
    unsigned int EBO = 0;
    unsigned int texture;
    int modelLoc;
    int viewLoc;
    int projectionLoc;

    void buildShaderProgram();
    void generateTexture();
    void setUPVertexAttributes();

public:
    ElementDrawer();
    virtual ~ElementDrawer();
    void draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
};


#endif