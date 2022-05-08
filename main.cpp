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

#include <iostream>
#include <string>
#include <memory>

// TODO list:
// - Key callback handler
// - Renderer

// Called once per frame
void Update()
{
    auto &context = Moxel::GLFW::GetContext();

    // -- Set to fullscreen after 3 seconds
    GLFWwindow *glfwWindowHandle = dynamic_cast<Moxel::GLFW::GLFWWindow *>(context.GetMainWindow().get())->GetGLFWWindowHandle();
    if (glfwGetTime() > 3 && glfwGetWindowMonitor(glfwWindowHandle) == nullptr)
    {
        context.GetMainWindow()->MakeFullscreen();
    }

    // -- Close after 7 seconds
    if (glfwGetTime() > 7)
    {
        context.SetLoopShouldExit(true);
    }
}

int main()
{
    auto &context = Moxel::GLFW::GetContext();
    Moxel::Window window = context.MakeWindow();

    window->SetTitle("Awesome Window");

    context.SetUpdateCallback(&Update);

    context.Start();
}