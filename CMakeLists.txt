cmake_minimum_required(VERSION 3.21)
project(MoxelEngine)
include(FetchContent REQUIRED)
include(ExternalProject REQUIRED)

FetchContent_Declare(
        glm_project
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG bf71a834948186f4097caa076cd2663c69a10e1e # release 0.9.9.8
)

FetchContent_Declare(
        glad_project
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG 1ecd45775d96f35170458e6b148eb0708967e402 # release 0.1.36
)

FetchContent_Declare(
        glfw_project
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 814b7929c5add4b0541ccad26fb81f28b71dc4d8 # release 3.4
)

FetchContent_Declare(
        freetype_project
        GIT_REPOSITORY https://gitlab.freedesktop.org/freetype/freetype.git
        GIT_TAG aee6b9472732c627ff844d4fb75a588d388b6570 # release 2.12.0
)

FetchContent_MakeAvailable(glm_project glad_project glfw_project freetype_project)

set(LIBS_DIR "${CMAKE_SOURCE_DIR}/libs")

file(DOWNLOAD
        https://raw.githubusercontent.com/nothings/stb/master/stb_image.h
        ${LIBS_DIR}/stb_image.h)

file(DOWNLOAD
        https://raw.githubusercontent.com/Reputeless/PerlinNoise/master/PerlinNoise.hpp
        ${LIBS_DIR}/PerlinNoise.hpp)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXE_LINKER_FLAGS "-static")
add_executable(MoxelEngine main.cpp src/GLFWInstance.cpp src/GLFWInstance.h src/WindowParams.cpp src/WindowParams.h src/World.cpp src/World.h src/Window.cpp src/Window.h)
target_link_libraries(MoxelEngine PUBLIC glm glad glfw freetype)

file(GLOB SHADERS_FOLDER "shaders/*.glsl")
file(GLOB TEXTURES_FOLDER "textures/*")
file(GLOB FONTS_FOLDER "fonts/*")
file(COPY ${SHADERS_FOLDER} DESTINATION shaders)
file(COPY ${TEXTURES_FOLDER} DESTINATION textures)
file(COPY ${FONTS_FOLDER} DESTINATION fonts)