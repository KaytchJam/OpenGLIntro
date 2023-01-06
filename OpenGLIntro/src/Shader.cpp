#include "Shader.h"
#include "ErrorManager.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& filepath) : m_FilePath(filepath), m_RendererID(0) {
    ShaderProgramSource source = parseShader(filepath);
    m_RendererID = createShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader() {
    GLCall(glDeleteProgram(m_RendererID));
}

/// <summary>
/// Parser for our .shader type files, reads the file source code and returns it as a string.
/// </summary>
/// <param name="filepath">filepath to the .shader file we want to use.</param>
/// <returns>Returns a ShaderProgramSource struct containing all shader source code strings as fields.</returns>
ShaderProgramSource Shader::parseShader(const std::string& filepath) {
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}


unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
    //std::printf("type: %x\n%s\n", type, source.c_str());
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str(); // returns a pointer to our source std::string
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    //std::cout << "Color error" << std::endl;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    //std::cout << "color error" << std::endl;

    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)_malloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(type);
        return 0;
    }

    return id;
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

   /* std::printf("vs: 0x%x\n", vs);
    std::printf("fs: 0x%x\n", fs);*/

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));

    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    // take care of the OBJ files
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

void Shader::Bind() const {
    GLCall(glUseProgram(m_RendererID));
}

void Shader::UnBind() const {
    GLCall(glUseProgram(0));
}

void Shader::setUniform1i(const std::string& name, int value) {
    GLCall(glUniform1i(getUniformLocation(name), value));
}

void Shader::setUniform1f(const std::string& name, float value) {
    GLCall(glUniform1f(getUniformLocation(name), value));
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
    GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniformMat4f(const std::string& name, glm::mat4& matrix) {
    GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::getUniformLocation(const std::string& name) {
    std::unordered_map<std::string, int>::iterator myIt = m_UniformLocationCache.find(name);
    if (myIt != m_UniformLocationCache.end()) {
        return myIt->second; // quick uniform location retrieval
    }

    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1) std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

    m_UniformLocationCache[name] = location;
	return location;
}