#version 450

layout(location = 0) in vec3 fragColor;    // Vertex shader’dan gelen renk
layout(location = 0) out vec4 outColor;

void main() {
    outColor = vec4(fragColor, 1.0);       // Alpha = 1
}
// Bu shader, vertex shader’dan gelen renk bilgisini alýr ve