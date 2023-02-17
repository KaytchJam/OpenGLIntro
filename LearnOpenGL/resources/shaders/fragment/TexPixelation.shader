#version 330 core

out FragColor;
in vec2 tCoords;

uniform sampler2D texture1;

void main() {
    float Pixels = 512.0;
    float dx = 15.0 * (1.0 / Pixels);
    float dy = 10.0 * (1.0 / Pixels);
    vec2 Coord = vec2(dx * floor(tCoords.x / dx),
        dy * floor(tCoords.y / dy));
    FragColor = texture(texture1, Coord);
}