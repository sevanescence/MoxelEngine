//
// Created by damia on 5/5/2022.
//

#ifndef MOXELENGINE_GLFWCONTEXT_H
#define MOXELENGINE_GLFWCONTEXT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"

#include <memory>

// TODO:
// Wrap a lot of OpenGL calls behind this header, including (but not limited to)
// renaming the window, arbitrary resizing, monitor and resolution, etc etc.

namespace Moxel
{
    /**
     * Manages OpenGL and GLFW boilerplate and essential functions and processes.
     * This class is a singleton and should not be instantiated directly,
     * but rather through Moxel::CreateGlobalContext
     */
    class GLFWContext
    {
        bool (*mLoopCallback)(GLFWContext &instance);
        bool mLoopShouldClose;
    public:
        GLFWContext();

        // TODO: I might make mLoopShouldClose a public attribute. As far as I can tell it would not change anything.

        /**
         * Manually set whether the loop should close (this is useful for callbacks handled
         * by the GLFWContext instance rather than directly in the instance loop).
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
         * Terminates GLFWContext. This is called at the end of Moxel::GLFWContext::Start().
         */
        void Terminate();

        /**
         * Sets the program loop for this instance.
         * @param loop A function callback. Return true to end loop.
         */
        void SetGLFWGraphicsLoopCallback(bool (*loop)(GLFWContext &instance));

        /**
         * Begin program loop. Once this ends, Moxel::GLFWContext::Terminate() is called.
         */
        void Start();
    };

    static std::shared_ptr<GLFWContext> globalContext;

    GLFWContext &GetGlobalContext();

    void DefaultFramebufferSizeCallback(GLFWwindow *window, int width, int height);
}

#endif //MOXELENGINE_GLFWCONTEXT_H
