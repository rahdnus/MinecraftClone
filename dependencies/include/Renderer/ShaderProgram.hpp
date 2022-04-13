#pragma once

#include<core.hpp>
#include<Renderer/Shader.hpp>
#include<glm.hpp>
namespace Core{

    class ShaderProgram
    {
        uint32_t ID;
        Shader vertexShader,fragmentShader;
        public:

        bool compile(const char* vertexPath,const char* fragmentPath);
        void bind();
        void unbind();
        
    };

}
