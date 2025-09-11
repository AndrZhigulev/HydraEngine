//
// Created by An-zh on 07.09.2025.
//
#pragma once
#define GLFW_INCLUDE_VULKAN
#include <iostream>
#include <optional>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <stdexcept>

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;
    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

class HydraEngine {
public:
    void startup();
    void shutdown();
    void run();

private:

    void initVulkan();
    void pickPhysicalDevice(); // our selection function
    void createSurface();
    void createLogicalDevice();
    //void findQueueFamilies();
    bool isDeviceSuitable(VkPhysicalDevice device); // a helper function to check a device
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    //QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    bool m_isRunning = false;
    GLFWwindow* m_window = nullptr; //Указатель на окно GLFW.

    VkInstance m_instance;
    VkSurfaceKHR m_surface;
    VkDevice m_device;
    VkQueue m_graphicsQueue;
    VkQueue m_presentQueue;
    // VK_NULL_HANDLE is the vulkan equivalent of nullptr for handles
    VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
};