//
// Created by damia on 5/5/2022.
//
#include "Moxel.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GLFWUtils.h"

void Moxel::InitializeGLFW()
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
}

void Moxel::TerminateGLFW()
{
    glfwTerminate();
}
