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

// Called once before the loop
void Initialize()
{
    Moxel::GetCurrentContext().GetMainWindow().MakeFullscreen();
}

// Called once per frame
void Update()
{
    using namespace Moxel;
    WindowContext context = GetCurrentContext();

    GLFWwindow *glfwWindowHandle = dynamic_cast<GLFW::GLFWWindow&>(context.GetMainWindow()).GetGLFWWindowHandle();
    if (glfwGetTime() > 3 && glfwGetWindowMonitor(glfwWindowHandle) != nullptr)
    {
        context.GetMainWindow().MakeWindowed();
    }

    if (glfwGetTime() > 7)
    {
        std::cout << "Five seconds have passed. Closing application.\n";
        context.SetContextShouldClose(true);
    }
}

int main()
{
    using namespace Moxel;
    WindowContext context = CreateContext<GLFW>();
    MakeContextCurrent(context);

    Window window = context.MakeWindow();
    window.SetTitle("Awesome Window");

    context.SetInitCallback(Initialize);
    context.SetUpdateCallback(Update);
    context.Start();
}