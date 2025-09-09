//
// Created by An-zh on 07.09.2025.
//
#pragma once
#define GLFW_INCLUDE_VULKAN
#include <iostream>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <stdexcept>

class HydraEngine {
public:
    void startup();
    void shutdown();
    void run();

private:

    void initVulkan();
    void pickPhysicalDevice(); // our selection function
    static bool isDeviceSuitable(VkPhysicalDevice device); // a helper function to check a device

    bool m_isRunning = false;
    GLFWwindow* m_window = nullptr; //Указатель на окно GLFW.

    VkInstance m_instance;
    // VK_NULL_HANDLE is the vulkan equivalent of nullptr for handles
    VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
};