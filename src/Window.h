//
// Created by damia on 5/5/2022.
//

#ifndef MOXELENGINE_WINDOW_H
#define MOXELENGINE_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Moxel
{
    class Window
    {
        GLFWwindow *mGLFWwindowPtr;
    public:
        Window();
        explicit Window(GLFWwindow *glfwWindow);


    };
}

#endif //MOXELENGINE_WINDOW_H
