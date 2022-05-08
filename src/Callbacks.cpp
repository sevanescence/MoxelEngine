//
// Created by damia on 5/5/2022.
//
#include "Callbacks.h"

void Moxel::Callbacks::DefaultFramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
