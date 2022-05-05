//
// Created by damia on 5/5/2022.
//

#ifndef MOXELENGINE_MOXEL_H
#define MOXELENGINE_MOXEL_H

#include "GLFWContext.h"
#include "GLFWUtils.h"
#include "Window.h"

namespace Moxel
{
    /**
     * Initializes GLFW. This is necessary for doing anything with the engine.
     */
    void InitializeGLFW();

    /**
     * Unloads GLFW functions and mappings. This is really only for the case where
     * the global context cant be terminated for some reason (like upon failure of
     * InitializeGLFW()).
     */
    void TerminateGLFW();
}

#endif //MOXELENGINE_MOXEL_H
