#pragma once
#include<core.hpp>
#include<math1.h>
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
    struct Vertex
    {
        glm::vec3 position;
        glm::vec4 color;

    };
}