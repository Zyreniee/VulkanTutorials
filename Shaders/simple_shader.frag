#version 450

// Vertex shader'dan gelen renk
layout(location = 0) in vec3 fragColor;

// Son pixel rengini çýkýþ olarak veriyoruz
layout(location = 0) out vec4 outColor;

void main() {
    // Alpha kanalý = 1.0 (tam opak)
    outColor = vec4(fragColor, 1.0);
    // Bu shader sadece vertex'ten gelen rengi alýr ve ekrana çizer
}
// Bu shader, basit bir renk çýkýþý saðlar