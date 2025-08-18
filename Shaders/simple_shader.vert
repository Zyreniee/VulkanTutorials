#version 450

layout(location = 0) in vec3 inPos;

layout(location = 1) in vec3 inColor;

layout(location = 0) out vec3 fragColor;

void main() {
    gl_Position = vec4(inPos, 1.0);

    // Alt kýsým hafif karanlýk efekti için y pozisyonuna göre renk modülasyonu
    float factor = 0.3 + 0.7 * (inPos.y + 1.0) / 2.0; 
    fragColor = inColor * factor;
        // fragColor = vec3(1.0, 0.0, 0.0); // Kýrmýzý
  
  // fragColor = vec3(0.0, 1.0, 0.0); // Yeþil
    // fragColor = vec3(0.0, 0.0, 1.0); // Mavi
    // fragColor = vec3(1.0, 1.0, 0.0); // Sarý
    // fragColor = vec3(0.0, 1.0, 1.0); // Camgöbeði
    // fragColor = vec3(1.0, 0.0, 1.0); // Magenta
    // fragColor = vec3(1.0, 1.0, 1.0); // Beyaz
    // fragColor = vec3(0.0, 0.0, 0.0); // Siyah

}
    