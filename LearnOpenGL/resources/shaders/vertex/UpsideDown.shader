#version 330 core

layout(location = 0) in vec3 positions;
out gl_Position;

void main()
{
	gl_Position = vec4(positions.x, positions.y * -1, positions.z, 1.0f);
}