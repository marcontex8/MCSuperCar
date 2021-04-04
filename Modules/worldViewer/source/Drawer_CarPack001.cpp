#include "Drawer_CarPack001.h"
#include "Factory_CarPack001.h"
#include "Diagnostics.h"

extern Diagnostics diagnostics;

CarPack001Drawer::CarPack001Drawer(std::vector<CarElement> elements):
	elements(elements) {}


void CarPack001Drawer::draw(glm::vec3 position, glm::quat orientation, Scene& scene) {

	for (const CarElement& element : elements) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, position);
		model = glm::translate(model, glm::vec3(0.0, 0.0, 0.4));
		model = glm::rotate(model, glm::angle(orientation), glm::axis(orientation));
		model = glm::scale(model, glm::vec3(0.001f, 0.001f, 0.001f));

		glBindVertexArray(element.VAO);
		glUseProgram(element.shaderProgram);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, element.texture_diffuse);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, element.texture_specular);

		glUniformMatrix4fv(element.viewLocation, 1, GL_FALSE, glm::value_ptr(scene.getView()));
		glUniformMatrix4fv(element.projectionLocation, 1, GL_FALSE, glm::value_ptr(scene.getProjection()));
		glUniformMatrix4fv(element.modelLocation, 1, GL_FALSE, glm::value_ptr(model));

		glm::vec3 lightColor	= scene.getLightColor();
		glm::vec3 lightPosition = scene.getLightPosition();
		glm::vec3 viewPos		= scene.getCameraPosition();

		glUniform3fv(element.light_positionLocation, 1, glm::value_ptr(lightPosition));
		glUniform3fv(element.viewPosLocation, 1, glm::value_ptr(viewPos));

		glUniform3fv(element.light_ambientLocation, 1, glm::value_ptr(lightColor * element.light_ambient));
		glUniform3fv(element.light_diffuseLocation, 1, glm::value_ptr(lightColor * element.light_diffuse));
		glUniform3fv(element.light_specularLocation, 1, glm::value_ptr(lightColor * element.light_specular));
		glUniform1f(element.mat_opacityLocation, element.mat_opacity);
		glUniform1f(element.mat_shininessLocation, element.mat_shininess);

		glDrawElements(GL_TRIANGLES, (GLsizei) element.indicesNumber, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}
