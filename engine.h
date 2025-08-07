#pragma once

#include "config.h"
#include "device.h"

namespace Engine {

    class Engine {
    public:
        void make_debug_messenger();  // Henüz tanýmlý deðil ama interface olarak býrakýldý
        void make_device();

        vk::PhysicalDevice getPhysicalDevice() const { return physicalDevice; }
        vk::Device getDevice() const { return device; }

    private:
        vk::Instance instance;                 // Vulkan instance
        vk::PhysicalDevice physicalDevice{};   // GPU
        vk::Device device{};                   // Logical device
        bool debugMode = true;                 // Debug modu açýk
    };

}
