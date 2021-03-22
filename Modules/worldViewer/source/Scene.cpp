#include "Scene.h"

Scene::Scene(float window_height, float window_width) :
	window_height(window_height),
	window_width(window_width),
	FOV(glm::radians(50.0f)),
	cameraPosition(glm::vec3(0.0f, 0.0f, 10.0)),
	lightPosition(glm::vec3(0.0f, 0.0f, 1000.0))
{
	evaluateProjection();
	evaluateView();
}

glm::mat4 Scene::getProjection() {
	return projection;
}

glm::mat4 Scene::getView() {
	return view;
}

void Scene::setFOV(float FOV) {
	this->FOV = FOV;
	evaluateProjection();
}

void Scene::setWindowSize(float height, float width) {
	this->window_height = height;
	this->window_width = width;
	evaluateProjection();
}

void Scene::setCameraPosition(glm::vec3 position) {
	this->cameraPosition = position;
	evaluateView();
}

void Scene::setLightPosition(glm::vec3 position) {
	this->lightPosition = position;
}

void Scene::setLightColor(glm::vec3 color) {
	this->lightColor = color;
}

glm::vec3 Scene::getLightPosition() {
	return this->lightPosition;
}

glm::vec3 Scene::getLightColor(){
	return this->lightColor;
}

glm::vec3 Scene::getCameraPosition() {
	return this->cameraPosition;
}

void Scene::evaluateProjection() {
	this->projection = glm::perspective(glm::radians(FOV), window_height / window_width, zNear, zFar);
}

void Scene::evaluateView() {
	view = glm::lookAt(cameraPosition,
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f));
}