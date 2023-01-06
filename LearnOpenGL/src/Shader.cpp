#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

static void errorCheck(unsigned int shader_obj, int success, char *infoLog)
{
	if (!success)
	{
		glGetShaderInfoLog(shader_obj, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED OR PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
} 

Shader::Shader(const char* vertexFilePath, const char* shaderFilePath) : program_ID(0)
{
	shaderCode sourceCodes = getShaderSourceCode(vertexFilePath, shaderFilePath);

	int success;
	char infoLog[512];

	unsigned int vs_ID, fs_ID;
	vs_ID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs_ID, 1, &sourceCodes.vertexSourceCode, NULL);
	glCompileShader(vs_ID);
	glGetShaderiv(vs_ID, GL_COMPILE_STATUS, &success);
	errorCheck(vs_ID, success, infoLog);

	fs_ID = glCreateShader(GL_FRAGMENT_SHADER);
	glCreateShader(GL_FRAGMENT_SHADER);
	glCompileShader(fs_ID);
	glGetShaderiv(fs_ID, GL_COMPILE_STATUS, &success);
	errorCheck(fs_ID, success, infoLog);

	program_ID = glCreateProgram();
	glAttachShader(program_ID, vs_ID);
	glAttachShader(program_ID, fs_ID);
	glLinkProgram(program_ID);

	int success;
	glGetProgramiv(program_ID, GL_LINK_STATUS, &success);
	errorCheck(program_ID, success, infoLog);

	glDeleteShader(vs_ID);
	glDeleteShader(fs_ID);
}

Shader::~Shader()
{
	glDeleteProgram(program_ID);
}

// SHADER CREATION
shaderCode getShaderSourceCode(const std::string& vertexFilePath, const std::string& fragmentFilePath)
{
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexFilePath);
		fShaderFile.open(fragmentFilePath);
		std::stringstream vStream, fStream;

		vStream << vShaderFile.rdbuf();
		fStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vStream.str();
		fragmentCode = fStream.str();
	}
	catch(std::ifstream::failure e)
	{
		std::cout << "SHADER::GET_SHADER_SOURCE::ERROR_DURING_FILE_READ" << std::endl;
	}

	return { vertexCode.c_str(), fragmentCode.c_str() };
}

// FLOAT UNIFORMS
void Shader::setUniform1f(const std::string& name, float v0) 
{
	glUniform1f(getUniformLocation(name), v0);
}

void Shader::setUniform2f(const std::string& name, float v0, float v1) 
{
	glUniform2f(getUniformLocation(name), v0, v1);
}

void Shader::setUniform3f(const std::string& name, float v0, float v1, float v2) 
{
	glUniform3f(getUniformLocation(name), v0, v1, v2);
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) 
{
	glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}

// INTEGER UNIFORMS
// BOOLEAN UNIFORMS
// UNSIGNED INT UNIFORMS

int Shader::getUniformLocation(const std::string& uniform_name)
{
	std::unordered_map<std::string, int>::iterator myIt = uniformLocationCache.find(uniform_name);
	if (myIt != uniformLocationCache.end()) 
	{
		return myIt->second; // quick uniform location retrieval
	}

	int location = glGetUniformLocation(program_ID, uniform_name.c_str());
	if (location == -1) std::cout << "Warning: uniform '" << uniform_name << "' doesn't exist in source code!" << std::endl;

	uniformLocationCache[uniform_name] = location;
	return location;
}


