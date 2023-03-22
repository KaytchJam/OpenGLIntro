#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "gl_tools/Shader.h"
#include "gl_tools/ErrorHandler.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum ShapeType {
	TRIANGLE,
	RECTANGLE,
	POLYGON,
	ELLIPSE
};

class Canvas2D {
private:
	int length, height;
	glm::mat4 proj, view;
public:
	Canvas2D(unsigned int length, unsigned int height);
	~Canvas2D();

	int getCanvasLength() const { return this->length; }
	int getCanvasHeight() const { return this->height; }
	void drawShape(Shape2D s, Shader sh);

};

class Shape2D {
private:
	unsigned int vao, vbo, ebo, txt;
	glm::mat4 model;
public:
	Shape2D() {}

	~Shape2D() {
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ebo);
		glDeleteTextures(1, &txt);
	}
};

class Square2D : Shape2D {
private:
	int length, height;
public:
};