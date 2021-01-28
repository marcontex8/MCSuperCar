#ifndef OPENGLDEFINITIONSFACTORY_H
#define OPENGLDEFINITIONSFACTORY_H

#include "ElementDrawer.h"
#include "BoxDrawer.h"

class Shaders {
public:
	const char* simpleVSCode = R"(
		#version 330 core
		layout (location = 0) in vec3 aPos;
		layout (location = 1) in vec2 aTexCoord;

		out vec2 TexCoord;

		uniform mat4 model;
		uniform mat4 view;
		uniform mat4 projection;

		void main()
		{
			gl_Position = projection * view * model * vec4(aPos, 1.0f);
			TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
		}
	)";

	const char* simpleFSCode = R"(
		#version 330 core
		out vec4 FragColor;

		in vec2 TexCoord;

		uniform sampler2D texture1;

		void main()
		{
			FragColor = texture(texture1, TexCoord, 0.2);
		}
	)";

	static unsigned int Shaders::compileShader(const char* shaderCode, GLenum type);
	static unsigned int buildShaderProgram(const char* vertexShaderCode, const char* fragmentShaderCode);
};


class Textures {
public:
	const char* boxTexturePath = R"(D:\WorkSpace\MCSuperCar\Modules\world_viewer\graphic\container.jpg)";
	static unsigned int generateTexture(const char* texturePath);
};


class Vertices {
public:
	size_t cubeTexturedSize = 5 * 6 * 6;
	float cubeTexturedVertices[5 * 6 * 6] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	static void Vertices::setUpVertices(float* verticesArray, size_t size, unsigned int& VBO, unsigned int& VAO);
};


class DrawersFactory {
private:
	Shaders shaders;
	Textures textures;
	Vertices vertices;
	unsigned int box_VAO = 0;
	unsigned int box_VBO = 0;
	unsigned int box_shaderProgram = 0;
	unsigned int box_texture = 0;
	unsigned int box_modelLoc = 0;
	unsigned int box_viewLoc = 0;
	unsigned int box_projectionLoc = 0;

public:
	DrawersFactory();
	~DrawersFactory();
	void setupBox();
	BoxDrawer* newBoxDrawer();
};


#endif