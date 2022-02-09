cmake_minimum_required(VERSION 3.21)
project(MoxelEngine)
include(FetchContent REQUIRED)

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

FetchContent_MakeAvailable(glm_project glad_project glfw_project)

set(CMAKE_CXX_STANDARD 23)

add_executable(MoxelEngine main.cpp)
target_link_libraries(MoxelEngine PUBLIC glad glfw)