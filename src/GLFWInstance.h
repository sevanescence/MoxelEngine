//
// Created by damia on 5/5/2022.
//

#ifndef MOXELENGINE_GLFWINSTANCE_H
#define MOXELENGINE_GLFWINSTANCE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "WindowParams.h"

// TODO:
// Wrap a lot of OpenGL calls behind this header, including (but not limited to)
// renaming the window, arbitrary resizing, monitor and resolution, etc etc.

namespace Moxel
{
    /**
     * Manages OpenGL and GLFW boilerplate and essential functions and processes.
     * This class is trivially movable (not copyable) but is still managed as a resource handler
     * to avoid ambiguity between truly copyable types.
     */
    class GLFWInstance
    {
        GLFWwindow *mWindow;
        WindowParams mWindowParams;

        bool (*mLoop)(GLFWInstance &instance);
        bool mLoopShouldClose;
    public:
        GLFWInstance();
        /**
         * Creates a GLFWInstance with defined parameters for how the managed window should behave.
         * @param window A struct that describes what parameters to pass to the managed window.
         */
        explicit GLFWInstance(WindowParams window);

        // TODO: I might make mLoopShouldClose a public attribute. As far as I can tell it would not change anything.

        /**
         * Manually set whether the loop should close (this is useful for callbacks handled
         * by the GLFWInstance instance rather than directly in the instance loop).
         * @param loopShouldClose
         */
        void SetLoopShouldClose(bool loopShouldClose);

        /**
         * Gets whether the loop should close or not. This member is not publicly accessible to avoid
         * unsafely writing to the object as well as to provide a more intuitive interface.
         * @return whether the loop should close.
         */
        [[nodiscard]] bool GetLoopShouldClose() const;

        /**
         * Initializes crucial GLFW processes and callbacks.
         */
        void Initialize();

        /**
         * Terminates GLFWInstance (destruction will not call this implicitly, it must
         * be called explicitly).
         */
        void Terminate();

        /**
         * Sets the program loop for this instance.
         * @param loop A function callback. Return true to end loop.
         */
        void SetGLFWGraphicsLoopCallback(bool (*loop)(GLFWInstance &instance));

        /**
         * Begin program loop.
         */
        void Start();
    };

    void DefaultFramebufferSizeCallback(GLFWwindow *window, int width, int height);
}

#endif //MOXELENGINE_GLFWINSTANCE_H
