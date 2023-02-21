#include "SegmentedDisplay.h"

void SegmentedDisplay::generateBuffers() {
	float vertices[] = {
		 0.0f, 0.5f, 0.0f, // leftmost
		0.25f, 0.0f, 0.0f, // bottom left
		0.25f, 1.0f, 0.0f, // top left
		0.75f, 1.0f, 0.0f, // top right
		0.75f, 0.0f, 0.0f, // bottom right
		 1.0f, 0.5f, 0.0f // right most
	};

	int indices[] = {
		0, 1, 2,
		2, 3, 1,
		1, 4, 3,
		3, 5, 4
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(GL_ARRAY_BUFFER, &vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
}

void SegmentedDisplay::initialize_segments() {
}

void SegmentedDisplay::set_input(uint8_t in) {
}

void SegmentedDisplay::update_segments() {
}

void SegmentedDisplay::print_signals() {
}

SegmentedDisplay::SegmentedDisplay(float x, float y, uint8_t in) : originX(x), originY(y), input(in) {
	initialize_segments();
	update_segments();
}

SegmentedDisplay::~SegmentedDisplay() {
}

void SegmentedDisplay::onUpdate(float deltaTime) {
}

void SegmentedDisplay::onRender() {
}
