#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "gl_tools/Shader.h"
#include "gl_tools/ErrorHandler.h"

// not sure if I'll create entire class variants of openGL entities

//class DShape {
//public:
//	DShape() {}
//	virtual ~DShape() {}
//	virtual void draw() {}
//};
//
//class DRect : DShape {
//private:
//	unsigned int vao, vbo, ebo;
//public:
//	DRect(float x, float y, float length, float height);
//	~DRect();
//};
//
//class DTriangle : DShape {
//private:
//	unsigned int vao, vbo;
//public:
//	DTriangle(float *d);
//	~DTriangle();
//};
