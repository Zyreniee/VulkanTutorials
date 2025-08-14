#version 450

// Vertex pozisyonu (giriþ)
layout(location = 0) in vec2 inPosition;
// Vertex rengi (giriþ)
layout(location = 1) in vec3 inColor;

// Fragment shader'a aktarýlacak renk (çýkýþ)
layout(location = 0) out vec3 fragColor;

void main() {
    // Pozisyonu 4 boyutlu vektöre dönüþtürüp ekrana gönder
    gl_Position = vec4(inPosition, 0.0, 1.0);
    // Rengi çýkýþa aktar
    fragColor = inColor;
}