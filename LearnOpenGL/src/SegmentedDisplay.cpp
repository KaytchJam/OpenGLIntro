#include "SegmentedDisplay.h"

void SegmentedDisplay::generateBuffers() {
	float vertices[] = {
		 0.0f, 0.5f, 0.0f, // leftmost
		0.25f, 0.0f, 0.0f, // bottom left
		0.25f, 1.0f, 0.0f, // top left
		0.75f, 1.0f, 0.0f, // top right
		0.75f, 0.0f, 0.0f, // bottom right
		 1.0f, 0.5f, 0.0f  // right most
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

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void setSegment(struct sig_segment *s, bool state, enum SegmentType s_type, char sym, float oX, float oY) {
	s->on = state;
	s->stype = s_type;
	s->symbol = sym;
	s->offsetX = oX;
	s->offsetY = oY;
}

void SegmentedDisplay::initialize_segments() {
	const char *symbols = "abfgced";
	const float HORIZONTAL_PADDING_L = 1 / 3;
	const float HORIZONTAL_PADDING_H = 0.2f;
	// SET HORIZONTALS
	for (int seg = 0; seg < NUM_SEGMENTS; seg += 3) {
		struct sig_segment cur_seg = segs[seg];
		setSegment(
			&cur_seg, 
			false, 
			SegmentType::HORIZONTAL, 
			symbols[seg], length * HORIZONTAL_PADDING_L, 
			height * (seg / (NUM_SEGMENTS - 1)) + (height * HORIZONTAL_PADDING_H)
		);
	}

	// SET VERTICALS
}

void SegmentedDisplay::set_input(uint8_t in) {

}

int SegmentedDisplay::get_input() {
	return input;
}

void SegmentedDisplay::update_segments() {
}

void SegmentedDisplay::print_signals() {
}

SegmentedDisplay::SegmentedDisplay(float x, float y, float aLength, float aHeight, const char *vs, const char *fs, uint8_t in) : 
	originX(x), originY(y), length(aLength), height(aHeight), input(in), sh(Shader(vs, fs)) {
	generateBuffers();
	initialize_segments();
	update_segments();
}

SegmentedDisplay::~SegmentedDisplay() {
}

void SegmentedDisplay::onUpdate(float deltaTime) {
}

void SegmentedDisplay::onRender() {
}
