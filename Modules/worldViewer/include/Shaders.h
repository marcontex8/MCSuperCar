#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"
#include <mutex>



class Shaders {
public:
	Shaders();
	~Shaders();

	unsigned int getBoxShader();
	unsigned int getSimpleScenarioShader();
	unsigned int getTextureCarShader();

private:
	static const char* simpleVSCode;
	static const char* simpleFSCode;

	static const char* simpleCarVSCode;
	static const char* simpleCarFSCode;

	static const char* textureCarVSCode;
	static const char* textureCarFSCode;

	static const char* simpleScenarioVSCode;
	static const char* simpleScenarioFSCode;

	unsigned int boxShader = 0;
	unsigned int simpleScenarioShader = 0;
	unsigned int textureCarShader = 0;

	void buildAllShaders();

	static unsigned int buildShaderProgram(const char* vertexShaderCode, const char* fragmentShaderCode);
	static unsigned int compileShader(const char* shaderCode, GLenum type);
};


#endif