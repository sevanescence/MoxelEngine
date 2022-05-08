//
// Created by damia on 5/5/2022.
//

#ifndef MOXELENGINE_GLFWCONTEXT_H
#define MOXELENGINE_GLFWCONTEXT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"

#include <string>
#include <memory>

// TODO:
// Wrap a lot of OpenGL calls behind this header, including (but not limited to)
// renaming the window, arbitrary resizing, monitor and resolution, etc etc.

#define GLAD_LOAD_FAILURE 0
#define GLFW_PRIMARY_MONITOR_IDX 0

namespace Moxel
{
    class IWindow;
    class GLFW;

    using Window = std::shared_ptr<IWindow>;

    class IWindow
    {
    public:
        virtual void SetTitle(const std::string &title) = 0;
        virtual void SetWindowSize(int width, int height) = 0;

        virtual std::string GetTitle() const = 0;
        virtual int GetHeight() const = 0;
        virtual int GetWidth() const = 0;

        virtual void MakeFullscreen(int idx) = 0;
        virtual void MakeFullscreen() = 0;
        virtual void MakeWindowed() = 0;
    };

    class GLFW
    {
    public:
        class GLFWWindow;
    private:
        void (*mUpdateCallback)();
        bool mLoopShouldExit;
        std::shared_ptr<GLFWWindow> mMainWindow;

        GLFW();
        ~GLFW();
    public:
        static GLFW &GetContext();

        bool GetLoopShouldExit() const;
        void SetLoopShouldExit(bool loopShouldExit);
        void SetUpdateCallback(void (*updateCallback)());

        Window GetMainWindow();

        Window MakeWindow();
        void Start();
        class GLFWWindow : public IWindow
        {
            friend GLFW;

            static bool sGladIsLoaded;
            static const char *sDefaultTitle;
            GLFWwindow *mWindowHandle{};

            std::string mTitle;
        public:
            GLFWWindow();
            ~GLFWWindow();
            void SetTitle(const std::string &title) override;
            void SetWindowSize(int width, int height) override;

            std::string GetTitle() const override;
            int GetHeight() const override;
            int GetWidth() const override;

            void MakeFullscreen(int idx) override;
            void MakeFullscreen() override;
            void MakeWindowed() override;

            // implementation-specific functions
            GLFWwindow *GetGLFWWindowHandle();
        };
    };
}

#endif //MOXELENGINE_GLFWCONTEXT_H
