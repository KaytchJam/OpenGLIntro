#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "gl_tools/Shader.h"
#include "gl_tools/ErrorHandler.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum ShapeType {
	RECTANGLE,
	POLYGON,
	ELLIPSE,
	COUNT = 3
};

class Shape2D {
private:
	unsigned int vao, vbo, ebo, txt;
	unsigned int ebo_count;
	glm::mat4 model;
public:
	Shape2D(ShapeType shape_type, float *data, unsigned int DATA_SIZE);
	~Shape2D() {
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ebo);
		glDeleteTextures(1, &txt);
	}

	// modifiers
	virtual void translate(float x, float y);
	virtual void translate(glm::vec2 trans_vec);
	virtual void rotate(float radians, glm::vec3 rotation_vec);

	// getters
	glm::mat4 *getModelMatrix() { return &model;  }
	unsigned int getVAO() const { return vao; }
	unsigned int getEBO_COUNT() const { return ebo_count; }

	//void scale(float scale_amount);
};

class Rect2D : public Shape2D {
private:
	float length, height;
	float x, y;
public:
	Rect2D(float x, float y, float length, float width);
	~Rect2D() {}

	// getters
	const float getLength() { return this->length; }
	const float getHeight() { return this->height; }
	const float getX() { return this->x; }
	const float getY() { return this->y; }
};

class Poly2D : public Shape2D {
private:
	float x, y;
public:
	Poly2D();
	~Poly2D();
};


class Canvas2D {
private:
	int length, height;
	glm::mat4 proj, view;
	Shader* sh;
public:

	// constructor
	Canvas2D(unsigned int length, unsigned int height, Shader *shader_program = NULL) {
		// setting fields
		this->proj = glm::ortho(0.0f, (float)length, 0.0f, (float)height, -1.0f, 1.0f);
		this->view = glm::mat4(1.0f); // identity matrix for now
		this->length = length;
		this->height = height;
		this->sh = shader_program;
	}

	// destructor
	~Canvas2D() {

	}

	int getCanvasLength() const { return this->length; }
	int getCanvasHeight() const { return this->height; }
	
	void renderShape(Shape2D& s) {
		this->sh->useShader();
		glm::mat4 MVP = this->proj * this->view * (*s.getModelMatrix());
		this->sh->setUniformMatrix4fv("MVP", 1, MVP);
		GLCall(glBindVertexArray(s.getVAO()));
		GLCall(glDrawElements(GL_TRIANGLES, s.getEBO_COUNT(), GL_UNSIGNED_INT, NULL));
	}

	void setShader(Shader *shader_program) {
		ASSERT(shader_program != NULL);
		this->sh = shader_program;
	}
};
