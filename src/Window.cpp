//
// Created by damia on 5/5/2022.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"

#include <iostream>
#include <utility>

Moxel::Window::Window() :
  mWindowHandle(nullptr)
{

}

Moxel::Window::Window(int width, int height, std::string title, GLFWmonitor *monitor, GLFWwindow *share) :
  mWidth(width),
  mHeight(height),
  mTitle(std::move(title)),
  mMonitor(monitor),
  mShare(share)
{

}

const GLFWwindow *Moxel::Window::GetWindowHandle() const
{
    return mWindowHandle;
}

GLFWwindow *Moxel::Window::GetWindowHandle()
{
    return mWindowHandle;
}

std::string Moxel::Window::GetTitle() const
{
    return mTitle;
}

void Moxel::Window::SetTitle(std::string title)
{
    mTitle = title;
    glfwSetWindowTitle(mWindowHandle, mTitle.c_str());
}

int Moxel::Window::GetWidth() const
{
    return mWidth;
}

int Moxel::Window::GetHeight() const
{
    return mHeight;
}

// TODO: handle the resize for the internal window handle.
void Moxel::Window::SetWindowSize(int width, int height)
{
    mWidth = width;
    mHeight = height;
    glfwSetWindowSize(mWindowHandle, width, height);
}

GLFWmonitor *Moxel::Window::GetMonitorHandle()
{
    return mMonitor;
}

void Moxel::Window::SetMonitorHandle(GLFWmonitor *monitor)
{
    mMonitor = monitor;
    if (monitor == nullptr)
    {
        glfwSetWindowMonitor(mWindowHandle, nullptr, mXPos, mYPos, mWidth, mHeight, 160);
    }
    else
    {
        const GLFWvidmode *vidMode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(
                mWindowHandle,
                monitor,
                0, 0,
                vidMode->width,
                vidMode->height,
                vidMode->refreshRate
                );
    }
}

void Moxel::Window::Initialize()
{
    mWindowHandle = glfwCreateWindow(
            mWidth,
            mHeight,
            mTitle.c_str(),
            mMonitor,
            mShare
            );
    if (mWindowHandle == nullptr)
    {
        throw "(Currently unmanaged) ERROR: GLFW window handle could not be initialized.";
    }
}

void Moxel::Window::Destroy()
{
    std::cout << "Destroying window " << mWindowHandle << '\n';
    glfwDestroyWindow(mWindowHandle);
    mWindowHandle = nullptr;
}

void Moxel::Window::SetFramebufferSizeCallback(void (*framebufferSizeCallback)(GLFWwindow *, int, int))
{
    mFramebufferSizeCallback = framebufferSizeCallback;
    glfwSetFramebufferSizeCallback(mWindowHandle, mFramebufferSizeCallback);
}

Moxel::Window &Moxel::GetWindow()
{
    using namespace Moxel;

    if (defaultWindow == nullptr)
    {
        defaultWindow = std::make_shared<Window>(
                800,
                600,
                "Default Moxel Window",
                nullptr,
                nullptr
                );
    }

    return *defaultWindow;
}
