#ifndef ASSIMPFACTORY_H
#define ASSIMPFACTORY_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>

#include "Shaders.h"
#include "Drawer_CarPack001.h"
#include "Definitions_CarPack001.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};


class CarPack001Factory {
private:
	//TODO: questa soluzione non mi piace, dovrei cambiarla
	carPack001::Paths currentPaths;
	std::vector<CarElement> carElements;

	Assimp::Importer importer;
	Shaders* shaders;

	std::map<std::tuple<carPack001::Model, carPack001::Color>, std::vector<CarElement>> customizations;

	const aiScene* loadModel(std::string const& path);
	void processNode(aiNode* node, const aiScene* scene);
	CarElement processMesh(aiMesh* mesh, const aiScene* scene, CarElement& element);

	static unsigned int loadTexture(std::string const& path);
	void processMaterial(aiMaterial* material, CarElement& element);
	void setupSimpleCar(carPack001::Model model, carPack001::Color color);

public:
	CarPack001Factory(Shaders* shaders);
	~CarPack001Factory();
	CarPack001Drawer* getNewSimpleCarDrawer(carPack001::Model model = carPack001::Model::Hatchback, carPack001::Color color = carPack001::Color::Blue);
};


#endif // !ASSIMPFACTORY_H
