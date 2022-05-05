//
// Created by damia on 5/5/2022.
//
#include "GLFWUtils.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWmonitor *Moxel::GetPrimaryMonitorHandle()
{
    return glfwGetPrimaryMonitor();
}

GLFWmonitor *Moxel::GetMonitorHandle(int idx)
{
    int count;
    GLFWmonitor **monitors = glfwGetMonitors(&count);
    if (idx >= count)
    {
        throw "Requested monitor index out of bounds.";
    }

    return monitors[idx];
}
