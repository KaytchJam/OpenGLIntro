#version 330 core

out vec4 FragColor;

in vec3 myColor;
in vec2 textureCoords;

uniform sampler2d ourTexture;

void main() {
	FragColor = (ourTexture, textureCoords);
}