#version 330 core

layout(location = 0) in vec3 positions;
layout(location = 1) in vec2 texCoords;

out vec2 tCoords;

void main() {
	gl_Positon = vec4(positions, 1.0);
	tCoords = texCoords;
}