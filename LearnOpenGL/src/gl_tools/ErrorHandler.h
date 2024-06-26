#pragma once
#include <glad/glad.h>
#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak()
#define GLCall(x) glClearError();\
    x;\
    ASSERT(glLogCall(#x, __FILE__, __LINE__))

void glClearError();
bool glLogCall(const char* function, const char* file, int line);
void allErrorsFound();
void shaderErrorCheck(int success, unsigned int shader_obj, char* infoLog);