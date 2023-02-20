#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "ErrorHandler.h"

static void errorCheck(unsigned int shader_obj, int success, char *infoLog, const char * type)
{
	if (!success)
	{
		glGetShaderInfoLog(shader_obj, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED OR PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
} 

Shader::Shader(const char *vertexFilePath, const char *fragmentFilePath) : program_ID(0)
{
	shaderCode sourceCodes = getShaderSourceCode(vertexFilePath, fragmentFilePath);
	std::printf("Vertex Shader: %s\n%s\n\n", vertexFilePath, sourceCodes.vertexSourceCode.c_str());
	std::printf("Fragment Shader: %s\n%s\n\n", fragmentFilePath, sourceCodes.fragmentSourceCode.c_str());

	int success;
	char infoLog[512];

	const char *vert  = sourceCodes.vertexSourceCode.c_str();
	const char *frag = sourceCodes.fragmentSourceCode.c_str();

	unsigned int vs_ID, fs_ID;
	vs_ID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs_ID, 1, &vert, NULL);;
	glCompileShader(vs_ID);
	glGetShaderiv(vs_ID, GL_COMPILE_STATUS, &success);
	errorCheck(vs_ID, success, infoLog, "VERTEX");

	fs_ID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs_ID, 1, &frag, NULL);
	glCompileShader(fs_ID);
	glGetShaderiv(fs_ID, GL_COMPILE_STATUS, &success);
	errorCheck(fs_ID, success, infoLog, "FRAGMENT");

	program_ID = glCreateProgram();
	glAttachShader(program_ID, vs_ID);
	glAttachShader(program_ID, fs_ID);
	glLinkProgram(program_ID);
	glGetProgramiv(program_ID, GL_LINK_STATUS, &success);
	errorCheck(program_ID, success, infoLog, "PROGRAM");

	glDeleteShader(vs_ID);
	glDeleteShader(fs_ID);

	std::cout << "Shader Constructed." << std::endl;
}

Shader::~Shader()
{
	glDeleteProgram(program_ID);
}

void Shader::useShader()
{
	glUseProgram(program_ID);
}

// SHADER CREATION
shaderCode Shader::getShaderSourceCode(const std::string& vertexFilePath, const std::string& fragmentFilePath)
{
	//std::cout << vertexFilePath << std::endl;
	//std::cout << fragmentFilePath << std::endl;

	std::string vertexCode, fragmentCode;
	std::ifstream vShaderFile, fShaderFile;

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

	return { vertexCode, fragmentCode };
}

// FLOAT UNIFORMS
void Shader::setUniform1f(const std::string& name, float v0) { glUniform1f(getUniformLocation(name), v0);  }
void Shader::setUniform2f(const std::string& name, float v0, float v1) { glUniform2f(getUniformLocation(name), v0, v1); }
void Shader::setUniform3f(const std::string& name, float v0, float v1, float v2) { glUniform3f(getUniformLocation(name), v0, v1, v2); }
void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) { glUniform4f(getUniformLocation(name), v0, v1, v2, v3); }
void Shader::setUniformMatrix4fv(const std::string& name, int num_matrices, glm::mat4& mat) { glUniformMatrix4fv(getUniformLocation(name), num_matrices, GL_FALSE, glm::value_ptr(mat)); }

// INTEGER UNIFORMS
void Shader::setUniform1i(const std::string& name, int v0) { glUniform1i(getUniformLocation(name), v0); }
// BOOLEAN UNIFORMS
void Shader::setUniform1b(const std::string& name, bool b0) { glUniform1i(getUniformLocation(name), b0); }
// UNSIGNED INT UNIFORMS

int Shader::getUniformLocation(const std::string& uniform_name)
{
	std::unordered_map<std::string, int>::iterator myIt = uniformLocationCache.find(uniform_name);
	if (myIt != uniformLocationCache.end()) 
	{
		return myIt->second; // quick uniform location retrieval
	}

	int location = glGetUniformLocation(program_ID, uniform_name.c_str());
	if (location == -1)
	{
		std::cout << "Warning: uniform '" << uniform_name << "' doesn't exist in source code!" << std::endl;
	}

	uniformLocationCache[uniform_name] = location;
	return location;
}


