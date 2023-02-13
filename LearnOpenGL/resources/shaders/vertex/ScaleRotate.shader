#version 330 core

layout(location = 0) in vec3 positions;
layout(location = 1) in vec2 texCoords;

out vec2 tCoords;
uniform mat4 transform;

void main() {
	gl_Position = transform * vec4(positions, 1.0f);
	tCoords = texCoords;
}