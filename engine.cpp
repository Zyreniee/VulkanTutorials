#include "device.h"
namespace Engine {

    void Engine::make_device() {
        physicalDevice = vkInit::choose_physical_device(instance, debugMode);
        device = vkInit::create_logical_device(physicalDevice, debugMode);
    }

    QueueFamilyIndices findQueueFamilies(vk::PhysicalDevice device, bool debug) {
        QueueFamilyIndices indices;

        auto queueFamilies = device.getQueueFamilyProperties();

        if (debug) {
            std::cout << "System can support " << queueFamilies.size() << " queue families" << std::endl;
        }

        for (uint32_t i = 0; i < queueFamilies.size(); ++i) {
            if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eGraphics) {
                indices.graphicsFamily = i;
                break;
            }
        }

        return indices;
    }

}