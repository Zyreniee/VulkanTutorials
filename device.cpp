#include "device.h"
#include <iostream>
#include <stdexcept>

namespace vkInit {

    bool QueueFamilyIndices::isComplete() const {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }

    QueueFamilyIndices findQueueFamilies(vk::PhysicalDevice device, bool debug) {
        QueueFamilyIndices indices;

        std::vector<vk::QueueFamilyProperties> queueFamilies = device.getQueueFamilyProperties();

        if (debug) {
            std::cout << "System supports " << queueFamilies.size() << " queue families." << std::endl;
        }

        for (uint32_t i = 0; i < queueFamilies.size(); i++) {
            if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eGraphics) {
                indices.graphicsFamily = i;
            }
            // Present family'yi istersen burada kontrol edebilirsin.
        }

        return indices;
    }

    vk::PhysicalDevice choose_physical_device(vk::Instance& instance, bool debug) {
        if (debug) {
            std::cout << "Choosing physical device..." << std::endl;
        }

        std::vector<vk::PhysicalDevice> devices = instance.enumeratePhysicalDevices();

        if (devices.empty()) {
            throw std::runtime_error("No physical devices found.");
        }

        if (debug) {
            std::cout << devices.size() << " physical device(s) found:" << std::endl;
            for (const auto& dev : devices) {
                auto props = dev.getProperties();
                std::cout << " - " << props.deviceName << std::endl;
            }
        }

        return devices[0]; // Basite ilk cihaz seiyoruz
    }

    vk::Device create_logical_device(vk::PhysicalDevice physicalDevice, bool debug) {
        QueueFamilyIndices indices = findQueueFamilies(physicalDevice, debug);

        if (!indices.graphicsFamily.has_value()) {
            throw std::runtime_error("Failed to find graphics queue family!");
        }

        float priority = 1.0f;
        vk::DeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &priority;

        std::vector<const char*> layers;
        if (debug) {
            layers.push_back("VK_LAYER_KHRONOS_validation");
        }

        vk::PhysicalDeviceFeatures features{};

        vk::DeviceCreateInfo createInfo{};
        createInfo.queueCreateInfoCount = 1;
        createInfo.pQueueCreateInfos = &queueCreateInfo;
        createInfo.enabledLayerCount = static_cast<uint32_t>(layers.size());
        createInfo.ppEnabledLayerNames = layers.data();
        createInfo.pEnabledFeatures = &features;

        try {
            return physicalDevice.createDevice(createInfo);
        }
        catch (const vk::SystemError& e) {
            if (debug) {
                std::cerr << "Device creation failed: " << e.what() << std::endl;
            }
            return vk::Device{};
        }
    }

}
