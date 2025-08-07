#pragma once

#include "config.h"
#include <iostream>
#include <stdexcept>
#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>
#include <optional>

namespace vkInit {

    // --- Struct tanýmýný dýþarý al ---
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() const {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    // --- Queue Family fonksiyonu ---
    inline QueueFamilyIndices findQueueFamilies(vk::PhysicalDevice device, bool debug) {
        QueueFamilyIndices indices;

        std::vector<vk::QueueFamilyProperties> queueFamilies = device.getQueueFamilyProperties();

        if (debug) {
            std::cout << "System can support " << queueFamilies.size() << " queue families" << std::endl;
        }

        for (uint32_t i = 0; i < queueFamilies.size(); i++) {
            if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eGraphics) {
                indices.graphicsFamily = i;
                break;
            }
        }

        return indices;
    }

    // --- Fiziksel cihaz seçme fonksiyonu ---
    inline vk::PhysicalDevice choose_physical_device(vk::Instance& instance, bool debug) {
        if (debug) {
            std::cout << "Choosing physical device..." << std::endl;
        }

        std::vector<vk::PhysicalDevice> availableDevices = instance.enumeratePhysicalDevices();

        if (availableDevices.empty()) {
            throw std::runtime_error("No physical devices found!");
        }

        if (debug) {
            std::cout << "There are " << availableDevices.size() << " physical device(s) available on this system" << std::endl;
            for (const auto& device : availableDevices) {
                auto props = device.getProperties();
                std::cout << " - " << props.deviceName << std::endl;
            }
        }

        // Ýsteðe baðlý olarak pause edebilirsin
        // system("pause"); // yorum satýrý yapabilirsin istersen

        return availableDevices[0]; // Þimdilik ilk cihazý döndürüyoruz
    }

    // --- Mantýksal cihaz oluþturma fonksiyonu (þimdilik boþ) ---
    vk::Device create_logical_device(vk::PhysicalDevice physicalDevice, bool debug) {
        QueueFamilyIndices indices = findQueueFamilies(physicalDevice, debug);
        float QueuePriority = 1.0f;
        vk::DeviceQueueCreateInfo queueCreateInfo = vk::DeviceQueueCreateInfo(
        vk::DevicqCreateFlags(),
        )

    }
}