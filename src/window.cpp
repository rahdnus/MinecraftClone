#include "window.h"
namespace window{
    bool _fullscreen=false;
   GLFWwindow* create()
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        // glfw window creation
        // --------------------
        GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,"LearnOpenGL", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return nullptr;
        }
        glfwMakeContextCurrent(window);
        return window;
    }
    void toggleFullscreen(GLFWwindow* window)
    {
        _fullscreen=!_fullscreen;

        glfwSetWindowMonitor(window,_fullscreen?glfwGetPrimaryMonitor():NULL,0,0,SCR_WIDTH,SCR_HEIGHT,GLFW_DONT_CARE);
    }
}
