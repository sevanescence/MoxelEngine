//
// Created by damia on 5/5/2022.
//

#include "WindowContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>

static std::shared_ptr<Moxel::IContext> _currentContext;
static std::vector<std::shared_ptr<Moxel::IContext>> _contexts;

void Moxel::MakeContextCurrent(Moxel::WindowContext context)
{
    auto ptr = &context;
    auto it = _contexts.begin();
    for (; it != _contexts.end(); ++it)
    {
        if (it->get() == ptr)
        {
            break;
        }
    }
    if (it == _contexts.end())
    {
        throw "WindowContext is not stored in context list. This is a fatal error and should be reported to the author.";
    }
    else
    {
        _currentContext = *it;
        std::cout << "WindowContext made current: " << _currentContext.get() << '\n';
    }
}

Moxel::WindowContext Moxel::GetCurrentContext()
{
    return *_currentContext;
}

std::vector<std::shared_ptr<Moxel::IContext>> &Moxel::GetDefinedContexts()
{
    return _contexts;
}

Moxel::GLFW::GLFW()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    std::cout << "GLFW initialized.\n";
}

Moxel::GLFW::~GLFW()
{
    glfwTerminate();

    std::cout << "GLFW terminated.\n";
}

Moxel::GLFW &Moxel::GLFW::GetContext()
{
    static GLFW context;
    return context;
}

bool Moxel::GLFW::GetContextShouldClose() const
{
    return mLoopShouldExit;
}

void Moxel::GLFW::SetContextShouldClose(bool contextShouldCLose)
{
    mLoopShouldExit = contextShouldCLose;
}

void Moxel::GLFW::SetUpdateCallback(void (*updateCallback)())
{
    mUpdateCallback = updateCallback;
}

void Moxel::GLFW::SetInitCallback(void (*initCallback)())
{
    mInitCallback = initCallback;
}

Moxel::Window Moxel::GLFW::GetMainWindow()
{
    return *mMainWindow;
}

Moxel::Window Moxel::GLFW::MakeWindow()
{
    auto window = std::make_shared<GLFW::GLFWWindow>();
    mMainWindow = window;
    return *window;
}

void Moxel::GLFW::Start()
{
    if (mInitCallback != nullptr)
        mInitCallback();
    while (not mLoopShouldExit)
    {
        /*
         * For now, we are going to use the  context of a single window. I am only doing
         * this to make development and testing a bit easier in the early stages. I will
         * eventually make a window context  manager and go through each existing window
         * and append a different renderer to  reach window (if I'm able to do that...).
         */

        mUpdateCallback();

        glfwSwapBuffers(mMainWindow->mWindowHandle);
        glfwPollEvents();
    }
}

bool Moxel::GLFW::GLFWWindow::sGladIsLoaded = false;
const char *Moxel::GLFW::GLFWWindow::sDefaultTitle = "Moxel GLFW Window";

Moxel::GLFW::GLFWWindow::GLFWWindow()
: mWindowHandle(
        glfwCreateWindow(
                800,
                600,
                sDefaultTitle,
                nullptr,
                nullptr)
        ),
        mTitle(sDefaultTitle)
{
    glfwMakeContextCurrent(mWindowHandle);

    if (not sGladIsLoaded)
    {
        if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) == GLAD_LOAD_FAILURE)
        {
            throw "Error: GLAD could not be loaded.";
        }

        sGladIsLoaded = true;
    }

    // -- Set callbacks

    std::cout << "GLFW window initialized.\n";
}

Moxel::GLFW::GLFWWindow::~GLFWWindow()
{
    glfwDestroyWindow(mWindowHandle);
    std::cout << "GLFW window destroyed.\n";
}

void Moxel::GLFW::GLFWWindow::SetTitle(const std::string &title)
{
    mTitle = title;
    glfwSetWindowTitle(mWindowHandle, mTitle.c_str());
}

void Moxel::GLFW::GLFWWindow::SetWindowSize(int width, int height)
{
    glfwSetWindowSize(mWindowHandle, width, height);
}

std::string Moxel::GLFW::GLFWWindow::GetTitle() const
{
    return mTitle;
}

int Moxel::GLFW::GLFWWindow::GetHeight() const
{
    int height;
    glfwGetWindowSize(mWindowHandle, nullptr, &height);
    return height;
}

int Moxel::GLFW::GLFWWindow::GetWidth() const
{
    int width;
    glfwGetWindowSize(mWindowHandle, &width, nullptr);
    return width;
}

void Moxel::GLFW::GLFWWindow::MakeFullscreen(int idx)
{
    int count;
    GLFWmonitor **monitors = glfwGetMonitors(&count);
    if (idx >= count)
    {
        throw "Error: Monitor index is out of bounds.";
    }

    GLFWmonitor *monitor = monitors[idx];
    const GLFWvidmode *vidmode = glfwGetVideoMode(monitor);

    glfwSetWindowMonitor(
            mWindowHandle,
            monitor,
            0, 0,
            vidmode->width,
            vidmode->height,
            vidmode->refreshRate
            );
}

void Moxel::GLFW::GLFWWindow::MakeFullscreen()
{
    MakeFullscreen(GLFW_PRIMARY_MONITOR_IDX);
}

void Moxel::GLFW::GLFWWindow::MakeWindowed()
{
    int width, height;
    glfwGetWindowSize(mWindowHandle, &width, &height);
    glfwSetWindowMonitor(mWindowHandle, nullptr, 100, 100, width, height, 60);
}

GLFWwindow *Moxel::GLFW::GLFWWindow::GetGLFWWindowHandle()
{
    return mWindowHandle;
}
