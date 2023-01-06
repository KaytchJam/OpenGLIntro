#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <unordered_map>
#include <string>

// each shader object will represent an instance of a "shader program"

class Shader
{
public:
	// program ID
	unsigned int object_ID;

	// constructor
	Shader(const char* vertexFilePath, const char* shaderFilePath);

	void useShader();
	void setUniform1f(const std::string& uniform_name, float v1);
	void setUniform2f(const std::string& uniform_name, float v1, float v2);
	void setUniform3f(const std::string& uniform_name, float v1, float v2, float v3);
	void setUniform4f(const std::string& uniform_name, float v1, float v2, float v3);

private:
	// a cache that'll store all our uniform locations
	std::unordered_map<std::string, int>  UniformLocationCache;
	int getUniformLocation(const std::string& uniform_name);
};
