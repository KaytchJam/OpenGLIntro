#version 330 core

out vec4 FragColor;
uniform int hex_color = 0x0; // pink color by default
float CEIL = 255.0f;
int BYTE_SIZE = 4;

vec4 parseColor(int colorHex) {
	vec4 colorVec = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	colorVec.z = (colorHex & 0xFF) / CEIL;
	colorVec.y = ((colorHex >> (2 * BYTE_SIZE)) & 0xFF) / CEIL;
	colorVec.x = ((colorHex >> (4 * BYTE_SIZE)) & 0xFF) / CEIL;
	return colorVec;
}

void main() 
{
	FragColor = parseColor(hex_color);
}