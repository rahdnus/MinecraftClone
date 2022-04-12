#pragma once
#include<core.hpp>

#include<stdio.h>
#include<string>

namespace Core
{
    class Application
    {
        GLFWwindow* mywindow;
        public:
            int windowInit(GLuint width,GLuint height,std::string name);
            int run();//mainLoop
    };
}