#version 330 core

layout(location = 0) in vec3 positions;

out vec4 pos;
// set our matrix uniforms to an I as default
uniform mat4 transform = mat4(1.0);
uniform mat4 MVP = mat4(1.0);

vec4 normalize_coords(in vec4 verts) {
	// will give a 2D view if no uniforms set
	return MVP * verts;
}

void main() {
	vec4 new_position = normalize_coords(transform * vec4(positions, 1.0f));
	gl_Position = new_position;
	pos = new_position;
}