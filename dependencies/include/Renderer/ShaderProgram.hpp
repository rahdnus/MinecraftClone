#pragma once

#include<core.hpp>
#include<Shader.hpp>
namespace Core{

    class ShaderProgram
    {
        GLint ID;
        Shader vertexShader,fragmentShader;
        public:

        bool compile(const char* vertexPath,const char* fragmentPath);
        void link();

        
    };

}
