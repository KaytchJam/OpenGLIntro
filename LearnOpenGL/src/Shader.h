#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <unordered_map>
#include <string>

struct shaderCode { const char *vertexSourceCode, *fragmentSourceCode; };

// each shader object will represent an instance of a "shader program"

class Shader
{
public:
	// program ID
	unsigned int program_ID;

	// constructor
	Shader(const char* vertexFilePath, const char* shaderFilePath);
	// destructor
	~Shader();

	// Shader Usage
	void useShader();

	// Uniform functions
	void setUniform1f(const std::string& uniform_name, float v0);
	void setUniform2f(const std::string& uniform_name, float v0, float v1);
	void setUniform3f(const std::string& uniform_name, float v0, float v1, float v2);
	void setUniform4f(const std::string& uniform_name, float v0, float v1, float v2, float v3);

private:
	// a cache that'll store all our uniform locations
	std::unordered_map<std::string, int>  uniformLocationCache;
	// store the code of our shader files as strings

	int getUniformLocation(const std::string& uniform_name);
	shaderCode getShaderSourceCode(const std::string& vertexFilePath, const std::string& fragmentFilePath);
};
