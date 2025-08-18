#version 450

layout(location = 0) in vec2 inPosition;

// Vertex shader'dan fragment shader'a renk gönderiyoruz
layout(location = 0) out vec3 fragColor;

void main() {
    // Vertex pozisyonu (x, y, z, w)
    gl_Position = vec4(inPosition, 0.0, 1.0);

    // Renk deðeri RGB formatýnda (0.0 - 1.0 aralýðýnda)
    // R = Kýrmýzý, G = Yeþil, B = Mavi
    // Örnek:
    // fragColor = vec3(1.0, 0.0, 0.0); // Kýrmýzý
    // fragColor = vec3(0.0, 1.0, 0.0); // Yeþil
    // fragColor = vec3(0.0, 0.0, 1.0); // Mavi
    // fragColor = vec3(1.0, 1.0, 0.0); // Sarý
    // fragColor = vec3(0.0, 1.0, 1.0); // Camgöbeði
    // fragColor = vec3(1.0, 0.0, 1.0); // Magenta
    // fragColor = vec3(1.0, 1.0, 1.0); // Beyaz
    // fragColor = vec3(0.0, 0.0, 0.0); // Siyah
    fragColor = vec3(1.0, 0.0, 0.0); // Kýrmýzý, burayý deðiþtirerek rengi deðiþtirebilirsin
}
// Bu shader, vertex pozisyonunu alýr ve fragment shader'a bir renk gönderir.