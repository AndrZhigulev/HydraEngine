//
// Created by An-zh on 07.09.2025.
//
#include "HydraEngine.h"
#include <iostream>
#include <vector>

void HydraEngine::startup() {
    std::cout << "Hydra Engine is starting..." << std::endl;
    //Инициализируем GLFW. Если не получилось выводим ошибку.
    if (!glfwInit()) {
        std::cout << "FATAL ERROR: Failed ti initialize GLFW!" << std::endl;
        return;

    }
    // We must tell GLFW NOT to create an OpenGL context
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    //Create window
    m_window = glfwCreateWindow(1024, 768, "Hydra Engine", nullptr, nullptr);
    if (!m_window) {
        glfwTerminate();
        return;
    }
    //initVulkan();
    m_isRunning = true;
    initVulkan();
    pickPhysicalDevice();
    m_isRunning = true;
}

void HydraEngine::pickPhysicalDevice() {
    // get the number of available GPUs
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("Failed to find GPUs with Vulkan support");
    }

    // allocate a vector to hold the handles to the GPUs
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices.data());

    std::cout << "Found " << deviceCount << " Vulkan-capable device(s)." << std::endl;

    // iterate through the available devices and pick the first suitable one
    for (const auto& device : devices) {
        if (isDeviceSuitable(device)) {
            m_physicalDevice = device;
            break; // we found what we wanted, no need to check others
        }
    }
    if (m_physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("Failed to find a suitable GPU!");
    }
}

bool HydraEngine::isDeviceSuitable(VkPhysicalDevice device) {
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);

    // we can also query for specific features
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    std::cout << "Checking devise: " << deviceProperties.deviceName << std::endl;

    // our main criteria; it MUST be a dedicated GPU
    bool isDiscrete = deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;

    // and for our future RTX featuries, it should support geometry shaders
    bool hasGeometryShader = deviceFeatures.geometryShader;

    return isDiscrete && hasGeometryShader;
}


void HydraEngine::run() {

    //игровой цикл будет работать пока юзер не закроет окно
    while (!glfwWindowShouldClose(m_window)) {
        // 1 input processing
        // processInput();
glfwPollEvents(); //проверяет все события
        // 2 logic updating
        // update();

        // 3 rendering
        // render();
        //std::cout << "Engine is running..." << std::endl;
        //m_isRunning = false;
    }

}

void HydraEngine::shutdown() {
    std::cout << "Hydra Engine is shutting down." << std::endl;
    vkDestroyInstance(m_instance, nullptr);
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void HydraEngine::initVulkan() {
    // --- Application Info ---
    // This struct is technically optional, but good practice to fill out.
    // It tells the driver some basic info about our app.
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hydra Engine";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "Hydra Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    // --- Instance Create Info ---
    // This struct tells Vulkan what global extensions and validation layers we want to use.
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // Vulkan is a platform-agnostic API, so you need an extension to interface with the window system.
    // GLFW has a handy function to return the extensions it needs.
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    // We aren't enabling any validation layers for now
    createInfo.enabledLayerCount = 0;

    // --- Create the Instance ---
    // vkCreateInstance returns a result code. We must check if it was successful.
    // VK_SUCCESS is the code for "everything is okay".
    VkResult result = vkCreateInstance(&createInfo, nullptr, &m_instance);
    if (result != VK_SUCCESS) {
        throw std::runtime_error("FATAL ERROR: failed to create instance!");
    }
    std::cout << "Vulkan Instance created successfully." << std::endl;
}