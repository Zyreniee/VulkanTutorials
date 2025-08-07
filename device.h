#pragma once

#include "config.h"
#include <iostream>
#include <stdexcept>
#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>
#include <optional>
#pragma once

#include <vulkan/vulkan.hpp>
#include <iostream>
#include "config.h"

namespace Engine {

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;

        bool isComplete() const {
            return graphicsFamily.has_value();
        }
    };

    class Engine {
    public:
        void make_device();
        vk::Device getDevice() const { return device; }

    private:
        vk::Instance instance;                  // Vulkan instance
        vk::PhysicalDevice physicalDevice;      // Seçilen fiziksel aygýt
        vk::Device device;                      // Mantýksal aygýt
        bool debugMode = true;                  // Debug modu aktif mi?
    };

    // Queue family bilgilerini bulma fonksiyonu
    QueueFamilyIndices findQueueFamilies(vk::PhysicalDevice device, bool debug);

}

namespace vkInit {

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() const {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    inline QueueFamilyIndices findQueueFamilies(vk::PhysicalDevice device, bool debug) {
        QueueFamilyIndices indices;

        std::vector<vk::QueueFamilyProperties> queueFamilies = device.getQueueFamilyProperties();

        if (debug) {
            std::cout << "System can support " << queueFamilies.size() << " queue families" << std::endl;
        }

        for (uint32_t i = 0; i < queueFamilies.size(); i++) {
            if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eGraphics) {
                indices.graphicsFamily = i;
                if (debug) {
                    std::cout << "Graphics queue family found at index " << i << std::endl;
                }
                break;
            }
        }

        return indices;
    }

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

        return availableDevices[0];
    }

    inline vk::Device create_logical_device(vk::PhysicalDevice physicalDevice, bool debug) {
        QueueFamilyIndices indices = findQueueFamilies(physicalDevice, debug);

        if (!indices.graphicsFamily.has_value()) {
            throw std::runtime_error("Failed to find graphics queue family!");
        }

        float queuePriority = 1.0f;
        vk::DeviceQueueCreateInfo queueCreateInfo{
            {},
            indices.graphicsFamily.value(),
            1,
            &queuePriority
        };

        std::vector<const char*> enabledLayers;
        if (debug) {
            enabledLayers.push_back("VK_LAYER_KHRONOS_validation");
        }

        vk::PhysicalDeviceFeatures deviceFeatures{};

        vk::DeviceCreateInfo createInfo{
            {},
            1,
            &queueCreateInfo,
            static_cast<uint32_t>(enabledLayers.size()),
            enabledLayers.data(),
            0,
            nullptr,
            &deviceFeatures
        };

        try {
            vk::Device device = physicalDevice.createDevice(createInfo);
            if (debug) {
                std::cout << "GPU has been successfully abstracted!" << std::endl;
            }
            return device;
        }
        catch (const vk::SystemError& err) {
            if (debug) {
                std::cerr << "Device creation failed: " << err.what() << std::endl;
            }
            return vk::Device{};
        }
    }

} // namespace vkInit
