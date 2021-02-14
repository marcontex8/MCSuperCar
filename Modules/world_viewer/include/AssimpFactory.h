#ifndef ASSIMPFACTORY_H
#define ASSIMPFACTORY_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>

#include "Shaders.h"
#include "SimpleCarDrawer.h"

struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	/*
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
	*/
};




class AssimpFactory {
private:
	const std::string simpleCarPath = R"(D:\WorkSpace\MCSuperCar\Modules\world_viewer\graphic\SimpleCar.obj)";
	
	Assimp::Importer importer;
	Shaders shaders;

	std::vector<CarElement> carElements;

	const aiScene* loadModel(std::string const& path);
	void processNode(aiNode* node, const aiScene* scene);
	CarElement processMesh(aiMesh* mesh, const aiScene* scene, CarElement& element);

	void setupSimpleCar();

public:
	AssimpFactory();
	~AssimpFactory();
	SimpleCarDrawer* getNewSimpleCarDrawer();


};


#endif // !ASSIMPFACTORY_H
