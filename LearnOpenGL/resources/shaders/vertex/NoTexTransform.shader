#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;

out vec4 ourColor;
uniform mat4 transform = mat4(1.0);

void main() {
	gl_Position = transform * vec4(pos, 1.0);
	ourColor = vec4(color, 1.0);
}