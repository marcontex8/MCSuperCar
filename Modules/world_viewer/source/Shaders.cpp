#include "Shaders.h"
#include "Diagnostics.h"


extern Diagnostics diagnostics;


const char* Shaders::simpleVSCode = R"(
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

const char* Shaders::simpleFSCode = R"(
		#version 330 core
		out vec4 FragColor;

		in vec2 TexCoord;

		uniform sampler2D texture1;

		void main()
		{
			FragColor = texture(texture1, TexCoord, 0.2);
		}
	)";

unsigned int Shaders::simpleCarShader = 0;
unsigned int Shaders::boxShader = 0;

Shaders::Shaders() {
	std::call_once(flag1, buildSimpleCarShader);
	std::call_once(flag2, buildBoxShader);
}

Shaders::~Shaders() {

}

void Shaders::buildSimpleCarShader() {
	simpleCarShader = buildShaderProgram(simpleVSCode, simpleFSCode);
}

void Shaders::buildBoxShader() {
	boxShader = buildShaderProgram(simpleVSCode, simpleFSCode);
}

unsigned int Shaders::compileShader(const char* shaderCode, GLenum type) {
	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderCode, NULL);
	glCompileShader(shader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return 0;
	}
	return shader;
};


unsigned int Shaders::buildShaderProgram(const char* vertexShaderCode, const char* fragmentShaderCode) {
	unsigned int vertexShader = 0;
	unsigned int fragmentShader = 0;

	vertexShader = compileShader(vertexShaderCode, GL_VERTEX_SHADER);
	if (vertexShader == 0) {
		std::cout << "Errore nella compiazione del vertex shader" << std::endl;
		return 0;
	}

	fragmentShader = compileShader(fragmentShaderCode, GL_FRAGMENT_SHADER);
	if (fragmentShader == 0) {
		std::cout << "Errore nella compiazione del fragment shader" << std::endl;
		return 0;
	}

	// link shaders
	int success = 0;
	char infoLog[512];
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return 0;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderProgram;
};

unsigned int Shaders::getBoxShader() {
	return boxShader;
}

unsigned int Shaders::gerSimpleCarShader() {
	return simpleCarShader;
}
