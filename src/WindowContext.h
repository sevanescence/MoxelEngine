//
// Created by damia on 5/5/2022.
//

#ifndef MOXELENGINE_WINDOWCONTEXT_H
#define MOXELENGINE_WINDOWCONTEXT_H

#include "Moxel.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <type_traits>
#include <iostream>
#include <vector>
#include <string>
#include <memory>

// TODO:
// Wrap a lot of OpenGL calls behind this header, including (but not limited to)
// renaming the window, arbitrary resizing, monitor and resolution, etc etc.

#define GLAD_LOAD_FAILURE 0
#define GLFW_PRIMARY_MONITOR_IDX 0

namespace Moxel
{
    class IContext;
    class IWindow;
    class GLFW;

    using Window = IWindow &;
    using WindowContext = IContext &;

    void MakeContextCurrent(WindowContext context);
    WindowContext GetCurrentContext();
    std::vector<std::shared_ptr<IContext>> &GetDefinedContexts();

    template <typename DerivedContextType>
    WindowContext CreateContext() requires(std::is_base_of_v<Moxel::IContext, DerivedContextType>)
    {
        auto context = std::make_shared<DerivedContextType>();
        GetDefinedContexts().push_back(context);
        return *context;
    }

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

    class IContext
    {
    public:
        virtual bool GetContextShouldClose() const = 0;
        virtual void SetContextShouldClose(bool contextShouldClose) = 0;
        virtual void SetUpdateCallback(void (*updateCallback)()) = 0;
        virtual void SetInitCallback(void (*initCallback)()) = 0;

        virtual Window GetMainWindow() = 0;
        virtual Window MakeWindow() = 0;

        virtual void Start() = 0;
    };

    class GLFW : public IContext
    {
    public:
        class GLFWWindow;
    private:
        bool mLoopShouldExit;
        std::shared_ptr<GLFWWindow> mMainWindow;
        void (*mUpdateCallback)() = 0;
        void (*mInitCallback)() = 0;

    public:
        GLFW();
        ~GLFW();
        static GLFW &GetContext();

        bool GetContextShouldClose() const override;
        void SetContextShouldClose(bool contextShouldCLose) override;
        void SetUpdateCallback(void (*updateCallback)()) override;
        void SetInitCallback(void (*initCallback)()) override;

        Window GetMainWindow() override;

        Window MakeWindow() override;
        void Start() override;
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

#endif //MOXELENGINE_WINDOWCONTEXT_H
