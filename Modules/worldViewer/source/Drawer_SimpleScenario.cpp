#include "Drawer_SimpleScenario.h"
#include "Shaders.h"
#include <iostream>
#include <string>

void SimpleScenarioDrawer::draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
    // draw our first triangle
    glUseProgram(shaderProgram);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);

    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 6);
}


SimpleScenarioDrawer::SimpleScenarioDrawer(unsigned int shaderProgram, unsigned int texture, unsigned int VAO, unsigned int viewLocation, unsigned int projectionLocation, unsigned int modelLocation) :
    shaderProgram(shaderProgram),
    texture(texture),
    VAO(VAO),
    viewLocation(viewLocation),
    projectionLocation(projectionLocation),
    modelLocation(modelLocation){
}