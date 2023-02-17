#version 330 core

layout(location = 0) in vec3 positions;
layout(location = 1) in vec2 texCoords;

out vec2 tCoords;
// set our matrix uniforms to an I as default
uniform mat4 transform = mat4(1.0);
uniform mat4 model = mat4(1.0);
uniform mat4 view = mat4(1.0);
uniform mat4 projection = mat4(1.0);

vec4 normalize_coords(in vec4 verts) {
	// will give a 2D view if no uniforms set
	return projection * view * model * verts;
}

void main() {
	gl_Position = normalize_coords(transform * vec4(positions, 1.0f));
	tCoords = texCoords;
}