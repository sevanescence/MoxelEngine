//
// Created by damia on 5/5/2022.
//

#include "GLFWInstance.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <utility>

#include "WindowParams.h"

Moxel::GLFWInstance::GLFWInstance()
: mWindow(nullptr),
mWindowParams(Moxel::GetDefaultWindow()),
mLoop(nullptr),
mLoopShouldClose(false)
{

}

Moxel::GLFWInstance::GLFWInstance(WindowParams window)
: mWindow(nullptr),
mWindowParams(std::move(window)),
mLoop(nullptr),
mLoopShouldClose(false)
{

}

void Moxel::GLFWInstance::SetLoopShouldClose(bool loopShouldClose)
{
    mLoopShouldClose = loopShouldClose;
}

bool Moxel::GLFWInstance::GetLoopShouldClose() const
{
    return mLoopShouldClose;
}

void Moxel::GLFWInstance::Initialize()
{
    // -- Initialize GLFW
    // TODO: make window hints modifiable. Will have hard values for now.
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // TODO: Catch and handle error properly
    GLFWwindow *window = Moxel::CreateGLFWWindow(mWindowParams);

    // TODO: This will have to be modifiable eventually, for dynamic window creation.
    glfwMakeContextCurrent(window);
    mWindow = window;

    if (not gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        throw "(Currently unmanaged) ERROR: GLAD could not be initialized. TODO: Make a proper error report.";
    }

    glViewport(0, 0, mWindowParams.width, mWindowParams.height);
    glfwSetFramebufferSizeCallback(window, &Moxel::DefaultFramebufferSizeCallback);
}

void Moxel::GLFWInstance::Terminate()
{
    // TODO: Free any buffers stored in here in the future (maybe give the end user an option to do this?)

    glfwDestroyWindow(mWindow);
    glfwTerminate();

    mWindow = nullptr;
    mLoopShouldClose = false;
}

void Moxel::DefaultFramebufferSizeCallback(GLFWwindow *, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Moxel::GLFWInstance::SetGLFWGraphicsLoopCallback(bool (*loop)(GLFWInstance &))
{
    mLoop = loop;
}

void Moxel::GLFWInstance::Start()
{
    // custom break condition for use by end user.
    while (not glfwWindowShouldClose(mWindow) && not mLoopShouldClose)
    {
        glfwSwapBuffers(mWindow);
        glfwPollEvents();

        mLoopShouldClose = mLoop(*this);
    }
}
