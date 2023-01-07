#version 330 core

in vec4 positions;
out vec4 FragColor;

void main()
{
	FragColor = positions;
}