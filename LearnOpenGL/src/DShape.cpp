#include "DShape.h"

void generateVertexArray(unsigned int *vao) {
	glGenVertexArrays(1, vao);
	glBindVertexArray(*vao);
}

void generateVertexBuffer(unsigned int *vbo, float *data, unsigned int NUM_ELEMENTS) {
	glGenBuffers(1, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glBufferData(GL_ARRAY_BUFFER, NUM_ELEMENTS * sizeof(float), data, GL_STATIC_DRAW);
}

void generateElementBuffer(unsigned int* ebo, float *indices) {

}

void unbindVertexArray(unsigned int* vao) {
	glBindVertexArray(0);
}

//DRect::DRect(float x, float y, float length, float width) {
//	generateVertexArray(&vao);
//
//	float vertices[] = {
//		0.0f, 0.0f, 0.0f,
//		length, 0.0f, 0.0f,
//		0.0f, width, 0.0f,
//		length, width, 0.0f
//	};
//
//	generateVertexBuffer(&vbo, vertices, 12);
//
//
//}