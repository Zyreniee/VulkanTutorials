#version 450 // GLSL sürümü 450, Vulkan için uygun

// Fragment shader çýktýsý (fragment color)
layout(location = 0) out vec4 outColor;

void main() {
    // Her pikselin rengini kýrmýzý olarak ayarla
    outColor = vec4(1.0, 0.0, 0.0, 1.0); // RGBA: kýrmýzý, yeþil, mavi, alpha
}
