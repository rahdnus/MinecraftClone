#include "input.h"

namespace input{
    bool keypressed[GLFW_KEY_LAST]={};
    bool mousepressed[GLFW_MOUSE_BUTTON_LAST]={};
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if(key>=0 && key<GLFW_KEY_LAST)
        {
            keypressed[key]=(action==GLFW_PRESS);
        }
        // switch (action)
        // {
        // case GLFW_PRESS:a
        //     printf("press");
        //     break;
        // case GLFW_RELEASE:
        //     printf("released");
        //     break;
        // case GLFW_REPEAT:
        //     printf("hold");
        //     break;
        // default:
        //     break;
        // }
        
    }
    void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
    {
        if(button>=0 && button<GLFW_MOUSE_BUTTON_LAST)
        {
            mousepressed[button]=action==GLFW_PRESS;
        }
    }

    bool key_down(int key)
    {
        if(key>=0 && key<GLFW_KEY_LAST)
        {
           return keypressed[key];
        }
         return false;
    }
    bool mouse_down(int key)
    {
        if(key>=0 && key<GLFW_MOUSE_BUTTON_LAST)
        {
            return mousepressed[key];
        }
        return false;
    }
}


