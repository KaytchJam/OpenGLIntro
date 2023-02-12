#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 colors;

out vec4 ourColor;
uniform mat4 transform;

void main() {
	gl_Position = transform * vec4(aPos, 1.0f);
	ourColor = vec4(colors, 1.0f);
}