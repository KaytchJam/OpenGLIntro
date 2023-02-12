#version 330 core

out vec4 FragColor;
in vec2 tCoords;
in vec4 ourColor;

uniform sampler2D texture1;
uniform bool textureSupplied;

void main() {
	if (textureSupplied == true) {
		FragColor = texture(texture1, tCoords);
	} else {
		FragColor = ourColor;
	}
}