#pragma once

#include<core.hpp>
#include<fstream>
#include<cstring>

namespace Core{namespace Shaders {

    enum class ShaderType:uint8_t
    {
        Vertex,Fragment
    };
    
    class Shader 
    {
       char* filepath;
       GLint ID;
       public:
        bool compile(ShaderType type,const char* path);
        void destroy();
        static GLenum toGLenumType(ShaderType type);
    };

}
}