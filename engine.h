#pragma once
#include "config.h"


class Engine {
public:
    void make_debug_messenger();
    void make_device();
};
namespace Engine {
    class Engine {
    public:
        void make_device();

    private:
        vk::Instance instance;                  // Vulkan instance
        vk::PhysicalDevice physicalDevice;      // GPU seçimi için
        bool debugMode = true;                  // debug flag
    };
}
