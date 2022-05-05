//
// Created by damia on 5/5/2022.
//

#ifndef MOXELENGINE_WINDOW_H
#define MOXELENGINE_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <memory>

namespace Moxel
{
    /**
     * Managed the internal GLFW window for this program. This is a singleton
     * and should not be instantiated directly, but rather through Moxel::GetWindow.
     */
    class Window
    {
        GLFWwindow *mWindowHandle;

        std::string mTitle;
        int mWidth;
        int mHeight;
        GLFWmonitor *mMonitor;
        GLFWwindow *mShare;

        /**
         * Position of windowed GLFW window. Values are arbitrary to ensure that the top bar
         * of the window is visible on the monitor.
         */
        int mXPos = 100;
        int mYPos = 100;

        void (*mFramebufferSizeCallback)(GLFWwindow *handle, int width, int height);
    public:
        Window();
        //explicit Window(GLFWwindow *glfwWindow);
        Window(int width, int height, std::string title, GLFWmonitor *monitor, GLFWwindow *share);

        /**
         * Get the internal GLFWwindow instance managed by this class.
         * @return a GLFWwindow
         */
        [[nodiscard]] const GLFWwindow *GetWindowHandle() const;

        /**
         * Get the internal GLFWwindow instance managed by this class.
         * @return a GLFWwindow
         */
        GLFWwindow *GetWindowHandle();

        [[nodiscard]] std::string GetTitle() const;

        /**
         * This is wrapped with a setter to handle internal glfw operations used to set the title.
         * @param title
         */
        void SetTitle(std::string title);

        [[nodiscard]] int GetWidth() const;

        [[nodiscard]] int GetHeight() const;

        /**
         * Changes the dimensions of a window. Handles internal processes for this action.
         * @param width
         * @param height
         */
        void SetWindowSize(int width, int height);

        /**
         * Gets the current monitor handle if in full screen.
         * @return returns the current monitor. Null if window is not in fullscreen mode.
         */
        GLFWmonitor *GetMonitorHandle();

        /**
         * Sets the current monitor handle and toggles fullscreen.
         * @param monitor The monitor handle. Set to null to toggle off fullscreen.
         */
        void SetMonitorHandle(GLFWmonitor *monitor);

        /**
         * Sets the framebuffer size callback for this window.
         * @param framebufferSizeCallback
         */
        void SetFramebufferSizeCallback(void (*framebufferSizeCallback)(GLFWwindow *, int, int));

        /**
         * Creates the GLFWwindow handle
         */
        void Initialize();

        /**
         * Destroy the GLFWwindow handle. This should only be called
         * on destruction of the Window object.
         */
        void Destroy();
    };

    static std::shared_ptr<Window> defaultWindow;

    Window &GetWindow();
}

#endif //MOXELENGINE_WINDOW_H
