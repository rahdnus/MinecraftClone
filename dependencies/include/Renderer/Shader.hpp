#pragma once

#include<core.hpp>

namespace Core{namespace Shaders {

    enum class ShaderType:uint8_t
    {
        Vertex,Fragment
    };
    
    class Shader 
    {
       char* readPath;
       public:
        bool compile(ShaderType type,const char* path);
        void destroy();
        static GLenum toGLenumType(ShaderType type);
    };

}
}