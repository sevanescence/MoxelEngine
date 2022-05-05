//
// Created by damia on 5/5/2022.
//

#ifndef MOXELENGINE_GLFWUTILS_H
#define MOXELENGINE_GLFWUTILS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Moxel
{
    /**
     * Gets the handle for the primary monitor.
     * @return the primary monitor.
     */
    GLFWmonitor *GetPrimaryMonitorHandle();

    /**
     * Gets a specific monitor. I
     * @param idx position of the monitor handle in the monitor array.
     * @return the monitor handle at idx.
     * @throws std::string if out of bounds (TODO: write proper exception)
     */
    GLFWmonitor *GetMonitorHandle(int idx);
}

#endif //MOXELENGINE_GLFWUTILS_H
