#pragma once
#include "core.h"
namespace Minecraft{
enum class ShaderType:uint8_t
{
    Vertex,
    Fragment
};

struct Shader
{
    char* filepath;
    uint32_t ShaderID;
    ShaderType type;
    
    bool compile(ShaderType type,const char* filepath);
    void destroy();
    static GLenum toglenumType(ShaderType type);
};
}
