#include "ElementDrawer.h"

#include <string>


ElementDrawer::ElementDrawer(ElementOpenGLDefinitions* openGLDefinitions){
    this->openglElements = openGLDefinitions;
    modelLoc = glGetUniformLocation(openglElements->getShaderProgram(), "model");
    viewLoc = glGetUniformLocation(openglElements->getShaderProgram(), "view");
    projectionLoc = glGetUniformLocation(openglElements->getShaderProgram(), "projection");

}

ElementDrawer::~ElementDrawer() {
    delete openglElements;
}


void ElementDrawer::draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, openglElements->getTexture());

    // draw our first triangle
    glUseProgram(openglElements->getShaderProgram());

    glBindVertexArray(openglElements->getVAO());
    glBindBuffer(GL_ARRAY_BUFFER, openglElements->getVBO());
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // set camera position and projection matrices
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glDrawArrays(GL_TRIANGLES, 0, 36);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
}