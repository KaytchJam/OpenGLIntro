#version 330 core

layout(location = 0) in vec3 positions;
layout(location = 1) in vec2 texCoords;

out vec2 tCoords;
uniform float xOffset;
uniform float yOffset;

void main() {
	gl_Positon = vec4(positions.x + xOffset, positions.y + yOffset, positons.z, 1.0);
	tCoords = texCoords;
}