#pragma once
#include<core.hpp>

namespace App
{
    class Application
    {
        GLFWwindow* mywindow;
        public:
            int WindowInit(GLuint width,GLuint height,std::string name);
            int Run();//mainLoop
    };
}