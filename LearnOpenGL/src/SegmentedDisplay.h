#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "gl_tools/Shader.h"
#include "gl_tools/ErrorHandler.h"

static const int NUM_SEGMENTS = 7;

static const enum SegmentType {
    HORIZONTAL = 0,
    VERTICAL = 1
};

// SEGMENT RELATED FIELDS:
// 1 means on, 0 means off - abcdefg
static const int8_t sig_mappings[10] = {
        0b1111110, // 0
        0b0110000, // 1
        0b1101101, // 2
        0b1111001, // 3
        0b0110011, // 4
        0b1011011, // 5
        0b1011111, // 6
        0b1110000, // 7
        0b1111111, // 8
        0b1111011  // 9
};

struct sig_segment {
    float x, y;
    bool on;
    SegmentType stype;
};

class SegmentedDisplay {
private:
    // RENDERING RELATED FIELDS:
    float originX, originY;
    int vtexture, htexture;
    GLuint vao, vbo, ebo, shader;

    // RENDERING RELATED FUNCTIONS
    void generateBuffers();
    void generateShaders();
    void generateTextures();

    // SEGMENT RELATED FIELDS
    uint8_t input = 0;
    struct sig_segment segs[NUM_SEGMENTS];
    
    // SEGMENT RELATED FUNCTIONS
    void initialize_segments();
    void set_input(uint8_t in);
    void update_segments();
    void print_signals();

public:
    SegmentedDisplay(float x, float y, uint8_t input);
    ~SegmentedDisplay();

    void onUpdate(float deltaTime);
    void onRender();
};