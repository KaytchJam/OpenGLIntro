#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <unordered_map>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct shaderCode { const std::string vertexSourceCode, fragmentSourceCode; };

// each shader object will represent an instance of a "shader program"

class Shader
{
private:
	// program ID
	unsigned int program_ID;
public:
	// constructor
	Shader(const char *vertexFilePath, const char *shaderFilePath);
	// destructor
	~Shader();

	// Shader Usage
	void useShader();

	// Uniform functions
	// floats
	void setUniform1f(const std::string& uniform_name, float v0);
	void setUniform2f(const std::string& uniform_name, float v0, float v1);
	void setUniform3f(const std::string& uniform_name, float v0, float v1, float v2);
	void setUniform4f(const std::string& uniform_name, float v0, float v1, float v2, float v3);
	void setUniformMatrix4fv(const std::string& uniform_name, int num_matrices, glm::mat4& mat);
	// integers
	void setUniform1i(const std::string& uniform_name, int v0);
	// boold
	void setUniform1b(const std::string& uniform_name, bool b0);

private:
	// a cache that'll store all our uniform locations
	std::unordered_map<std::string, int>  uniformLocationCache;
	// store the code of our shader files as strings

	int getUniformLocation(const std::string& uniform_name);
	shaderCode getShaderSourceCode(const std::string& vertexFilePath, const std::string& fragmentFilePath);
};
