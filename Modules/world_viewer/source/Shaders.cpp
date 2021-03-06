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

const char* Shaders::textureCarVSCode = R"(
		#version 330 core
		layout (location = 0) in vec3 aPos;
		layout (location = 1) in vec3 aNormal;
		layout (location = 2) in vec2 aTexCoords;

		uniform mat4 model;
		uniform mat4 view;
		uniform mat4 projection;

		out vec3 FragPos;  
		out vec3 Normal;
		out vec2 TexCoords;

		void main()
		{
			FragPos = vec3(model * vec4(aPos, 1.0));
			Normal = mat3(transpose(inverse(model))) * aNormal;  
			TexCoords = aTexCoords;
    
			gl_Position = projection * view * vec4(FragPos, 1.0);
		}
	)";

const char* Shaders::textureCarFSCode = R"(
		#version 330 core

		in vec3 FragPos;		
		in vec3 Normal;
		in vec2 TexCoords;

		out vec4 FragColor;

		struct Material {
			sampler2D diffuse;
			sampler2D specular;
			float     shininess;
			float	  opacity;
		}; 

		struct Light {
			vec3 position;

			vec3 ambient;
			vec3 diffuse;
			vec3 specular;
		};
  
		uniform Material material;
		uniform Light light;
		uniform vec3 viewPos;

		void main()
		{
			// ambient
			vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
  	
			// diffuse 
			vec3 norm = normalize(Normal);
			vec3 lightDir = normalize(light.position - FragPos);
			float diff = max(dot(norm, lightDir), 0.0);
			vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
    
			// specular
			vec3 viewDir = normalize(viewPos - FragPos);
			vec3 reflectDir = reflect(-lightDir, norm);  
			float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
			vec3 specularSample = vec3(texture(material.specular, TexCoords));			
			vec3 specular = light.specular * spec * specularSample.rrr;

			vec3 result = ambient + diffuse + specular;
			FragColor = vec4(result, material.opacity);
		}
	)";



const char* Shaders::simpleScenarioVSCode = R"(
		#version 330 core
		layout (location = 0) in vec3 aPos;
		layout (location = 1) in vec2 aTexCoord;

		uniform mat4 model;
		uniform mat4 view;
		uniform mat4 projection;
		uniform vec3 offsets[100];

		out vec2 TexCoord;

		void main()
		{
		    vec3 offset = offsets[gl_InstanceID];
			gl_Position = projection * view * model * vec4(aPos + offset, 1.0f);
			TexCoord = vec2(aTexCoord.x, aTexCoord.y);
		}
	)";


const char* Shaders::simpleScenarioFSCode = R"(
		#version 330 core

		in vec2 TexCoord;
		out vec4 FragColor;
		uniform sampler2D texture1;

		void main()
		{
			FragColor = texture(texture1, TexCoord, 0.2);
		}
	)";


unsigned int Shaders::boxShader = 0;
unsigned int Shaders::simpleScenarioShader = 0;
unsigned int Shaders::textureCarShader = 0;


Shaders::Shaders() {
	std::call_once(flag2, buildBoxShader);
	std::call_once(flag3, buildSimpleScenarioShader);
	std::call_once(flag4, buildTextureCarShader);
}

Shaders::~Shaders() {

}

void Shaders::buildTextureCarShader() {
	diagnostics.log("Building TextureCar Shader", Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Debug);
	textureCarShader = buildShaderProgram(textureCarVSCode, textureCarFSCode);
}

void Shaders::buildBoxShader() {
	diagnostics.log("Building Box Shader", Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Debug);
	boxShader = buildShaderProgram(simpleVSCode, simpleFSCode);
}

void Shaders::buildSimpleScenarioShader() {
	diagnostics.log("Building SimpleScenario Shader", Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Debug);
	simpleScenarioShader = buildShaderProgram(simpleScenarioVSCode, simpleScenarioFSCode);
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
		if (type == GL_VERTEX_SHADER) {
			diagnostics.log("VERTEX SHADER: COMPILATION_FAILED", Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Error);
		}
		if (type == GL_FRAGMENT_SHADER) {
			diagnostics.log("FRAGMENT SHADER: COMPILATION_FAILED", Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Error);
		}
		diagnostics.log(infoLog, Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Error);
		return 0;
	}
	if (type == GL_VERTEX_SHADER) {
		diagnostics.log("VERTEX SHADER: compiled sucessfully", Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Debug);
	}
	if (type == GL_FRAGMENT_SHADER) {
		diagnostics.log("FRAGMENT SHADER: compiled sucessfully", Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Debug);
	}
	return shader;
};


unsigned int Shaders::buildShaderProgram(const char* vertexShaderCode, const char* fragmentShaderCode) {
	unsigned int vertexShader = 0;
	unsigned int fragmentShader = 0;

	vertexShader = compileShader(vertexShaderCode, GL_VERTEX_SHADER);
	if (vertexShader == 0) {
		return 0;
	}

	fragmentShader = compileShader(fragmentShaderCode, GL_FRAGMENT_SHADER);
	if (fragmentShader == 0) {
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
		diagnostics.log("ERROR::SHADER::PROGRAM::LINKING_FAILED", Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Error);
		diagnostics.log(infoLog, Diagnostics::Topic::Viewer, Diagnostics::Verbosity::Error);
		return 0;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderProgram;
};

unsigned int Shaders::getBoxShader() {
	return boxShader;
}

unsigned int Shaders::getSimpleScenarioShader() {
	return simpleScenarioShader;
}

unsigned int Shaders::getTextureCarShader() {
	return textureCarShader;
}
