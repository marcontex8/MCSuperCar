#ifndef SCENE_H
#define SCENE_H

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Scene {
private:
	const float zNear = 0.1f;
	const float zFar = 500.0f;

	float window_height;
	float window_width;
	float FOV;
	
	glm::vec3 cameraPosition;
	glm::vec3 lightPosition;
	glm::vec3 lightColor;

	glm::mat4 projection;
	glm::mat4 view;


	void evaluateProjection();
	void evaluateView();

public:

	Scene(float window_height, float window_width);

	glm::mat4 getProjection();
	glm::mat4 getView();
	glm::vec3 getLightPosition();
	glm::vec3 getCameraPosition();
	glm::vec3 getLightColor();
	
	void setFOV(float FOV);
	void setWindowSize(float height, float width);
	void setCameraPosition(glm::vec3 position);
	void setLightPosition(glm::vec3 position);
	void setLightColor(glm::vec3 color);

};



#endif