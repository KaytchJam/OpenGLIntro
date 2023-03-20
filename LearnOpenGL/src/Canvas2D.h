#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "gl_tools/Shader.h"
#include "gl_tools/ErrorHandler.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Canvas2D {
private:
	int length, height;
	glm::mat4 proj, view;
public:
	Canvas2D(unsigned int length, unsigned int height);
	~Canvas2D();

	int getCanvasLength() const { return length; }
	int getCanvasHeight() const { return height; }

};