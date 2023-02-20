#version 330 core

out vec4 FragColor;
in vec2 tCoords;
in vec4 gl_FragCoord;

uniform sampler2D texture1;
uniform bool scanlines = false;

// returns whether some float coordScalar % modulo == 0
bool coordMod(in float coordScalar, in int modulo) {
    return int(coordScalar) % modulo == 0;
}

// Draws horizontal lines at every frag coordinate where 
// fragCoord.y % (modulo + range) == 0
vec4 makeScanlines(in vec4 fragVec, in int modulo, in int range) {
    bool clear = true;

    for (int offset = -1 * range; offset <= range; offset++) {
        clear = bool(int(clear) * int(!coordMod(gl_FragCoord.y, modulo + offset)));
    }

    return vec4(fragVec.x * float(clear), fragVec.yzw);
}

void main() {
    float Pixels = 512.0;
    float dx = 15.0 * (1.0 / Pixels);
    float dy = 10.0 * (1.0 / Pixels);
    vec2 Coord = vec2(dx * floor(tCoords.x / dx), dy * floor(tCoords.y / dy));

    vec4 fragPre = texture(texture1, Coord);
    if (scanlines) fragPre = makeScanlines(fragPre, 20, 2);
    FragColor = fragPre;
}