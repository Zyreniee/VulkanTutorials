#pragma once
#include "config.h"
#include <iostream>
#include <stdexcept>        // runtime_error için
#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

namespace vkInit {

    vk::PhysicalDevice choose_physical_device(vk::Instance& instance, bool debug) {
        if (debug) {
            std::cout << "Choosing physical device..." << std::endl;
        }

        // GPU'larý al
        std::vector<vk::PhysicalDevice> availableDevices = instance.enumeratePhysicalDevices();

        if (debug) {
            std::cout << "There are " << availableDevices.size() << " physical device(s) available on this system" << std::endl;
        }

        if (availableDevices.empty()) {
            throw std::runtime_error("No physical devices found!");
        }

        // Cihazlarýn isimlerini debug modunda yazdýr
        if (debug) {
            for (const auto& device : availableDevices) {
                vk::PhysicalDeviceProperties props = device.getProperties();
                std::cout << " - " << props.deviceName << std::endl;
            }
        }
        std::cout << "There are " << availableDevices.size() << " devices\n";
        for (auto& device : availableDevices) {
            auto props = device.getProperties();
            std::cout << " - " << props.deviceName << std::endl;
        }
        system("pause"); // Konsolun hemen kapanmasýný önler
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

        // Þimdilik ilk GPU'yu döndürüyoruz
        return availableDevices[0];
    }

}
