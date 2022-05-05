/**
 * Driver code to test library. The library is currently compiled as an executable
 * for ease of testing. Intend to scale to a proper library before production.
 */

// ChunkSystem chunkSystem(Dimensions: {x: 16, y: 16, z: 16});
// World world(ChunkSystem: chunkSystem, Generator: {Type: Perlin_Default, Seed: seed});
// not really sure how to design the rendering world system right now, so I'll leave it like this

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "src/GLFWInstance.h"
#include "src/WindowParams.h"

#include <iostream>
#include <string>
#include <memory>

bool loop(Moxel::GLFWInstance &instance)
{
    static double deltaTime = 0;
    if (deltaTime + 1 < glfwGetTime())
    {
        std::cout << "A second has passed.\n";
        deltaTime = glfwGetTime();
    }
    return false;
}

int main()
{
    // TODO: RAII and proper resource management for instance.
    Moxel::GLFWInstance instance(Moxel::CreateWindow(800, 800, "A Neat Window"));

    // TODO: Throw error if #Start is called before #Initialize
    instance.SetGLFWGraphicsLoopCallback(&loop);
    instance.Initialize();
    instance.Start();
    instance.Terminate();
}