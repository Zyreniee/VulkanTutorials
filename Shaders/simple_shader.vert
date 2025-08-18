#version 450

layout(location = 0) in vec2 inPosition;   // Vertex pozisyonu
layout(location = 1) in vec3 inColor;      // Vertex rengi

layout(location = 0) out vec3 fragColor;   // Fragment shader’a geçecek renk

void main() {
    fragColor = inColor;
    gl_Position = vec4(inPosition, 0.0, 1.0); // 2D pozisyon -> clip space
}
// gl_Position, 4D vektör olarak tanýmlanýr (x, y, z, w)    