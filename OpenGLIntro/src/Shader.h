#pragma once
#include <string>
#include <unordered_map>

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
	void setUniform4f(const std::string& name, float v0, float v1, float f2, float f3);
private:
	ShaderProgramSource parseShader(const std::string& filepath);
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int getUniformLocation(const std::string& name);
};