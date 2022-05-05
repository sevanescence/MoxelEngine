/**
 * Driver code to test library. The library is currently compiled as an executable
 * for ease of testing. Intend to scale to a proper library before production.
 */

// ChunkSystem chunkSystem(Dimensions: {x: 16, y: 16, z: 16});
// World world(ChunkSystem: chunkSystem, Generator: {Type: Perlin_Default, Seed: seed});
// not really sure how to design the rendering world system right now, so I'll leave it like this

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "src/Moxel.h"
#include "src/GLFWContext.h"
#include "src/Window.h"
#include "src/GLFWUtils.h"

#include <iostream>
#include <string>
#include <memory>

// TODO list:
// - Key callback handler
// - Renderer

bool loop(Moxel::GLFWContext &instance)
{
    static double deltaTime = 0;
    if (deltaTime + 1 < glfwGetTime())
    {
        std::cout << "A second has passed.\n";
        deltaTime = glfwGetTime();
    }

    if (glfwGetKey(Moxel::GetWindow().GetWindowHandle(), GLFW_KEY_F11) == GLFW_PRESS)
    {
        Moxel::GetWindow().SetMonitorHandle(Moxel::GetPrimaryMonitorHandle());
    }
    else if (glfwGetKey(Moxel::GetWindow().GetWindowHandle(), GLFW_KEY_F10) == GLFW_PRESS)
    {
        Moxel::GetWindow().SetMonitorHandle(nullptr);
    }

    return glfwGetKey(Moxel::GetWindow().GetWindowHandle(), GLFW_KEY_ESCAPE) == GLFW_PRESS;
}

int main()
{
    try
    {
        Moxel::InitializeGLFW();
    }
    catch (const char *s)
    {
        std::cout << s;
        Moxel::TerminateGLFW();
        return 1;
    }
    Moxel::GetGlobalContext().Initialize();
    Moxel::GetGlobalContext().SetGLFWGraphicsLoopCallback(&loop);

    Moxel::GetWindow().SetTitle("An interesting title.");

    Moxel::GetGlobalContext().Start();
}