//
// Created by damia on 5/5/2022.
//

#include "WindowParams.h"

#include <utility>

Moxel::WindowParams Moxel::GetDefaultWindow()
{
    using namespace Moxel;

    static WindowParams defaultWindow
    {
        800,
        600,
        "Default Moxel WindowParams",
        nullptr,
        nullptr
    };

    return defaultWindow;
}

Moxel::WindowParams Moxel::CreateWindow(int width, int height, std::string title)
{
    using namespace Moxel;

    WindowParams customWindow
    {
        width,
        height,
        std::move(title),
        nullptr,
        nullptr
    };

    return customWindow;
}

GLFWwindow *Moxel::CreateGLFWWindow(WindowParams window)
{
    GLFWwindow *glfwWindow = glfwCreateWindow(
            window.width,
            window.height,
            window.title.c_str(),
            window.monitor,
            window.share
    );

    if (glfwWindow == nullptr)
    {
        throw "(Currently unmanaged) ERROR: GLFWwindow could not be initialized. TODO: Make a proper error report.";
    }

    return glfwWindow;
}
