#include "Drawer_SimpleTerrain.h"
#include "Shaders.h"
#include <iostream>
#include <string>

void SimpleTerrainDrawer::draw(glm::vec3 position, glm::quat orientation, Scene& scene) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::angle(orientation), glm::axis(orientation));
    model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));



    // draw our first triangle
    glUseProgram(shaderProgram);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);

    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(scene.getView()));
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(scene.getProjection()));
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 6);
}


SimpleTerrainDrawer::SimpleTerrainDrawer(unsigned int shaderProgram, unsigned int texture, unsigned int VAO, unsigned int viewLocation, unsigned int projectionLocation, unsigned int modelLocation) :
    shaderProgram(shaderProgram),
    texture(texture),
    VAO(VAO),
    viewLocation(viewLocation),
    projectionLocation(projectionLocation),
    modelLocation(modelLocation){
}