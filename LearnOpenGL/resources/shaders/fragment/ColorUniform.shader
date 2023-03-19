#version 330 core

out vec4 FragColor;
uniform int hex_color = 0x0; // pink color by default
float CEIL = 255.0f;
const int BYTE_SIZE = 4;

// Takes in a hexcode and breaks it up into an RGB vector
vec4 parseColor(int colorHex) {
	vec4 colorVec = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	colorVec.b = (colorHex & 0xFF) / CEIL;
	colorVec.g = ((colorHex >> (2 * BYTE_SIZE)) & 0xFF) / CEIL;
	colorVec.r = ((colorHex >> (4 * BYTE_SIZE)) & 0xFF) / CEIL;
	return colorVec;
}

void main() 
{
	FragColor = parseColor(hex_color);
}