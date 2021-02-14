#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"
#include <mutex>



class Shaders {
public:
	Shaders();
	~Shaders();

	unsigned int getBoxShader();
	unsigned int gerSimpleCarShader();

private:
	std::once_flag flag1, flag2;
	static const char* simpleVSCode;
	static const char* simpleFSCode;

	static unsigned int simpleCarShader;
	static unsigned int boxShader;

	static void buildSimpleCarShader();
	static void buildBoxShader();

	static unsigned int buildShaderProgram(const char* vertexShaderCode, const char* fragmentShaderCode);
	static unsigned int compileShader(const char* shaderCode, GLenum type);
};


#endif