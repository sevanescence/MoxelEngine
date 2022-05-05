//
// Created by damia on 5/5/2022.
//

#include "GLFWContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <utility>

#include "Window.h"

// -- Global context

Moxel::GLFWContext &Moxel::GetGlobalContext()
{
    using namespace Moxel;
    if (globalContext == nullptr)
    {
        globalContext = std::make_shared<GLFWContext>();
    }

    return *globalContext;
}

// -- GLFWContext

Moxel::GLFWContext::GLFWContext() :
  mLoopCallback(nullptr),
  mLoopShouldClose(false)
{

}

void Moxel::GLFWContext::SetLoopShouldClose(bool loopShouldClose)
{
    mLoopShouldClose = loopShouldClose;
}

bool Moxel::GLFWContext::GetLoopShouldClose() const
{
    return mLoopShouldClose;
}

void Moxel::GLFWContext::Initialize()
{
    // TODO: This will have to be modifiable eventually, for dynamic window creation.
    Moxel::GetWindow().Initialize();
    glfwMakeContextCurrent(Moxel::GetWindow().GetWindowHandle());

    if (not gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        throw "(Currently unmanaged) ERROR: GLAD could not be initialized. TODO: Make a proper error report.";
    }

    glViewport(0, 0, Moxel::GetWindow().GetWidth(), Moxel::GetWindow().GetHeight());
    Moxel::GetWindow().SetFramebufferSizeCallback(&DefaultFramebufferSizeCallback);
}

void Moxel::GLFWContext::Terminate()
{
    // TODO: Free any buffers stored in here in the future (maybe give the end user an option to do this?)
    // ^ this will be done in the Renderer

    glfwDestroyWindow(Moxel::GetWindow().GetWindowHandle());
    glfwTerminate();

    mLoopShouldClose = false;
    std::cout << "GLFWContext terminated.\n";
}

void Moxel::DefaultFramebufferSizeCallback(GLFWwindow *, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Moxel::GLFWContext::SetGLFWGraphicsLoopCallback(bool (*loop)(GLFWContext &))
{
    mLoopCallback = loop;
}

void Moxel::GLFWContext::Start()
{
    // custom break condition for use by end user.
    while (not glfwWindowShouldClose(Moxel::GetWindow().GetWindowHandle()) && not mLoopShouldClose)
    {
        glfwSwapBuffers(Moxel::GetWindow().GetWindowHandle());
        glfwPollEvents();

        mLoopShouldClose = mLoopCallback(*this);
    }

    Terminate();
}
