#include "ErrorHandler.h"

void glClearError() {
    while (glGetError());
}

bool glLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << " " << line << std::endl;
        return false;
    }
    return true;
}

void allErrorsFound()
{
	GLenum current_error = glGetError();
	while (current_error)
	{
		std::cout << "Error (" << current_error << ") found." << std::endl;
		current_error = glGetError();
	}
}


void shaderErrorCheck(int success, unsigned int shader_obj, char* infoLog)
{
	if (!success)
	{
		glGetShaderInfoLog(shader_obj, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}
