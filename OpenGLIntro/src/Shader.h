#pragma once
#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

/// <summary>
/// Struct with the source code of our shader types as string fields
/// </summary>
struct ShaderProgramSource {
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader {
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
	// caching system for uniforms
public:
	Shader(const std::string& filename);
	~Shader();

	void Bind() const;
	void UnBind() const;

	// Set Uniforms
	void setUniform1i(const std::string& name, int value);
	void setUniform1f(const std::string& name, float value);
	void setUniform4f(const std::string& name, float v0, float v1, float f2, float f3);
	void setUniformMat4f(const std::string& name, glm::mat4& matrix);
private:
	ShaderProgramSource parseShader(const std::string& filepath);
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
	int getUniformLocation(const std::string& name);
};