#version 330 core

layout(location = 0) in vec3 positions;

void main()
{
	gl_Position = (positions.x, position.y * -1, positions.y, 1.0f);
}