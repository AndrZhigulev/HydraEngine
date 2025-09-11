cmake_minimum_required(VERSION 3.28)
project(HydraEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

find_package(Vulkan REQUIRED) # This command finds the Vulkan SDK

include(FetchContent)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4   # версия (можно поменять на новее)
)

FetchContent_MakeAvailable(glfw)

add_executable(HydraEngine main.cpp HydraEngine.cpp HydraEngine.h)
target_link_libraries(HydraEngine Vulkan::Vulkan glfw)