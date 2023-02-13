#version 330 core

layout(location = 0) in vec3 aPos;
out vec4 positions;

uniform float xOffset;
uniform float yOffset;
uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos.x + xOffset, aPos.y + yOffset, aPos.z, 1.0f);
}