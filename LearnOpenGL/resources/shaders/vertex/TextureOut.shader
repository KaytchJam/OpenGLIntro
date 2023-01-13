#version 330 core

layout(location = 0) in vec3 myPos;
layout(location = 1) in vec3 myColor;
layout(location = 2) in vec2 myTextureCoords;

out vec3 ourColor;
out vec2 textureCoords;

void main() {
	gl_Position = vec4(myPos, 1.0);
	ourColor = myColor;
	textureCoords = myTextureCoords;
}