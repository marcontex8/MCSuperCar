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

		glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
		glBindTexture(GL_TEXTURE_2D, element.texture_diffuse);

		glActiveTexture(GL_TEXTURE1); // activate the texture unit first before binding texture
		glBindTexture(GL_TEXTURE_2D, element.texture_specular);

		glUniformMatrix4fv(element.viewLocation, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(element.projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(element.modelLocation, 1, GL_FALSE, glm::value_ptr(model));

		glm::vec3 lightColor{ 1.0f, 1.0f, 1.0f };
		glm::vec3 objectColor{ 50.0/255, 98.0 / 255, 168.0 / 255 };
		glm::vec3 lightPosition{ 100.0f, 100.0f, 100.0f };
		glm::vec3 viewPos{ 0.0f, 0.0f, -3.0f };


		unsigned int mat_shininessLocation;
		unsigned int light_ambient;
		unsigned int light_diffuse;
		unsigned int light_specular;


		//glUniform3fv(element.lightColor,1, glm::value_ptr(lightColor));
		//glUniform3fv(element.objectColor, 1, glm::value_ptr(objectColor));
		glUniform3fv(element.light_positionLocation, 1, glm::value_ptr(lightPosition));
		glUniform3fv(element.viewPosLocation, 1, glm::value_ptr(viewPos));

		glUniform3fv(element.light_ambientLocation, 1, glm::value_ptr(element.light_ambient));
		glUniform3fv(element.light_diffuseLocation, 1, glm::value_ptr(element.light_diffuse));
		glUniform3fv(element.light_specularLocation, 1, glm::value_ptr(element.light_specular));
		glUniform1f(element.mat_opacityLocation, element.mat_opacity);
		glUniform1f(element.mat_shininessLocation, element.mat_shininess);

		
		glDrawElements(GL_TRIANGLES, element.indicesNumber, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}
