#pragma once

#include<core.hpp>
#include<Renderer/Shader.hpp>
#include<glm.hpp>
namespace Core{

    class ShaderProgram
    {
        Shader vertexShader,fragmentShader;
        public:
        uint32_t ID;

        bool compile(const char* vertexPath,const char* fragmentPath);
        void bind();
        void unbind();
        
    };

}
