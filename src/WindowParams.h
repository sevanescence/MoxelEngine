//
// Created by damia on 5/5/2022.
//

#ifndef MOXELENGINE_WINDOWPARAMS_H
#define MOXELENGINE_WINDOWPARAMS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

namespace Moxel
{
    /**
     * A trivially constructable GLFWwindow parameter structure to make GLFWInstance initialization a bit more
     * intuitive. Usually created with a WindowParams factory in the same header.
     */
    struct WindowParams
    {
        int width;
        int height;
        std::string title;
        GLFWmonitor *monitor;
        GLFWwindow *share;
    };

    /**
     * Returns a default window for with 800x600 resolution and title "Default Moxel WindowParams" for
     * ease of testing.
     * @return a window parameter struct.
     */
    WindowParams GetDefaultWindow();

    /**
     * Creates a WindowParams structure with the following parameters.
     * @param width width of the window
     * @param height height of the window
     * @param title title of the window
     * @return a WindowParams struct.
     */
    WindowParams CreateWindow(int width, int height, std::string title);

    GLFWwindow *CreateGLFWWindow(WindowParams window);
}


#endif //MOXELENGINE_WINDOWPARAMS_H
