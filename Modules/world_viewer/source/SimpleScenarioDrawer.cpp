#include "SimpleScenarioDrawer.h"
#include "Shaders.h"
#include <iostream>
#include <string>

void SimpleScenarioDrawer::draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
    // draw our first triangle
    glUseProgram(shaderProgram);

    glm::vec3 translations[100*100];
    int index = 0;
    float offset = 1.0f;
    for (int y = -10; y < 10; y += 2)
    {
        for (int x = -10; x < 10; x += 2)
        {
            glm::vec3 translation;
            translation.x = (float)x / 1.0f + offset;
            translation.y = (float)y / 1.0f + offset;
            translation.z = 0.0f;
            translations[index++] = translation;
        }
    }

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);

    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
    for (unsigned int i = 0; i < 100; i++)
    {
        std::string name = "offsets[" + std::to_string(i) + "]";
        unsigned int translationsLoc = glGetUniformLocation(shaderProgram, name.c_str());
        glUniform3fv(translationsLoc, 1, glm::value_ptr(translations[i]));
    }
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);
}


SimpleScenarioDrawer::SimpleScenarioDrawer(unsigned int shaderProgram, unsigned int texture, unsigned int VAO, unsigned int VBO, unsigned int viewLocation, unsigned int projectionLocation, unsigned int modelLocation) :
    shaderProgram(shaderProgram),
    texture(texture),
    VAO(VAO),
    VBO(VBO),
    viewLocation(viewLocation),
    projectionLocation(projectionLocation),
    modelLocation(modelLocation){
}