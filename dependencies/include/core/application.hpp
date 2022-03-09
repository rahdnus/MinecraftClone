#pragma once

#include "core.h"
#include "core/window.h"
#include "core/input.h"
#include "math1.h"
#include "renderer.h"
#include "challenge.hpp"

namespace Minecraft{namespace Application{
    extern GLFWwindow* window;
    bool Init();
    void Run();
}}