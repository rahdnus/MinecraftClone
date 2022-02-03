#pragma once

#include "core.h"

namespace window{

    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    extern bool _fullscreen;

    void toggleFullscreen(GLFWwindow* window);
    GLFWwindow* create();
}
