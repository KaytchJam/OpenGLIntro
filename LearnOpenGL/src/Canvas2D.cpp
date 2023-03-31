#include <iostream>
#include "Canvas2D.h"

void setShapeBufferData(ShapeType shape_type, float *data, int DATA_SIZE, unsigned int *vbo, unsigned int *ebo, unsigned int *ebo_count) {

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, *vbo));
	switch (shape_type) {
		case ShapeType::RECTANGLE:
		{
			printf("Initializing Rectangle buffer stuffs.\n");
			float vertices[] = {
				   0.0f,    0.0f, 0.0f,
				   0.0f, data[3], 0.0f,
				data[2], data[3], 0.0f,
				data[2],    0.0f, 0.0f
			};

			unsigned int indices[] = {
				0, 1, 2,
				2, 3, 0
			};

			GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo));
			GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

			GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL));
			GLCall(glEnableVertexAttribArray(0));

			*ebo_count = sizeof(indices) / sizeof(float);
			break;
		}
		case ShapeType::POLYGON:
		{
			break;
		}
		case ShapeType::ELLIPSE:
		{
			break;
		};
	}
}

Shape2D::Shape2D(ShapeType shape_type, float *data, unsigned int DATA_SIZE) {

	GLCall(glGenVertexArrays(1, &this->vao));
	GLCall(glBindVertexArray(this->vao));

	GLCall(glGenBuffers(1, &this->vbo));
	GLCall(glGenBuffers(1, &this->ebo));

	setShapeBufferData(shape_type, data, DATA_SIZE, &this->vbo, &this->ebo, &this->ebo_count);

	this->model = glm::translate(glm::mat4(1.0f), glm::vec3(data[0], data[1], 0.0f));
	this->txt = 0;
}

void Shape2D::translate(float x, float y) {
	model = glm::translate(model, glm::vec3(x, y, 0));
}

void Shape2D::rotate(float radians, glm::vec3 rotate_vec) {
	model = glm::rotate(model, radians, rotate_vec);
}

Rect2D::Rect2D(float x, float y, float length, float height)
	: Shape2D(ShapeType::RECTANGLE, std::vector<float>({x, y, length, height}).data(), 4) {
	this->x = x;
	this->y = y;
	this->length = length;
	this->height = height;
}