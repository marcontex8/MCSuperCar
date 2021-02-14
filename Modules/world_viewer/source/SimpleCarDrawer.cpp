#include "SimpleCarDrawer.h"
#include "AssimpFactory.h"
#include "Diagnostics.h"

extern Diagnostics diagnostics;

SimpleCarDrawer::SimpleCarDrawer(std::vector<CarElement> elements):
	elements(elements) {}


void SimpleCarDrawer::draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection) {

	for (const CarElement& element : elements) {
		// draw mesh
		diagnostics.monitor("element.VAO", std::to_string(element.VAO));
		diagnostics.monitor("element.indicesNumber", std::to_string(element.indicesNumber));
		//diagnostics.log("Draw called", Diagnostics::Topic::Viewer);
		glBindVertexArray(element.VAO);
		glUseProgram(element.shaderProgram);

		glUniformMatrix4fv(element.viewLocation, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(element.projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(element.modelLocation, 1, GL_FALSE, glm::value_ptr(model));

		glDrawElements(GL_TRIANGLES, element.indicesNumber, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}
