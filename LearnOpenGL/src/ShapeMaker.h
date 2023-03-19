#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "gl_tools/Shader.h"
#include "gl_tools/ErrorHandler.h"

class ShapeMaker2D {
private:
public:
	void make_square();
	void make_triangle();
};

class ShapeMaker3D {
private:
	void generate_vertices(unsigned int dim);
	void generate_indices(unsigned int dim);
public:
	void make_plane(unsigned int dim);
};