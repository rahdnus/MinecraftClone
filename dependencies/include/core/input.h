#pragma once

#include "core.h"
namespace input{
    extern bool keypressed[GLFW_KEY_LAST];
    extern bool mousepressed[GLFW_MOUSE_BUTTON_LAST];

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

    bool key_down(int key);
    bool mouse_down(int key);
}
