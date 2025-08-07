#pragma once

#include <vulkan/vulkan.hpp>



class Engine {
public:
    Engine();
    ~Engine();

    void make_device();
    void make_instance();
    
    vk::Device getDevice() const { return device; }
    vk::Instance getInstance() const { return instance; }
    vk::DebugUtilsMessengerEXT getDebugMessenger() const { return debugMessenger; }

private:
    void build_glfw_window();
    vk::Instance instance;
    vk::PhysicalDevice physicalDevice;
    vk::Queue presentQueue{ nullptr };  
    vk::Device device;
    vk::DebugUtilsMessengerEXT debugMessenger;
    bool debugMode;
    VkDebugUtilsMessengerCreateInfoEXT populateDebugMessengerCreateInfo();
    void setupDebugMessenger();
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageTypes,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData);


    vk::SurfaceKHR surface;
    
};

}
