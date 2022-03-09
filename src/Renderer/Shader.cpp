#include "Shader.hpp"
#include <cstring>
#include<vector>
#include<fstream>

namespace Minecraft
{
    static std::string ReadFile(const char* sourcefilepath);

    bool Shader::compile(ShaderType type, const char *sourcefilepath)
    {
        int strlength = strlen(sourcefilepath);
        filepath = (char *)std::malloc(sizeof(char) * (strlength + 1));

        std::strcpy(filepath, sourcefilepath);
        filepath[strlength] = '\0';

        GLenum gltype = toglenumType(type);

        if (gltype == GL_INVALID_ENUM)
        {
            printf("GL_Invalid_ENum\n");
            return false;
        }

        std::string shadersourcecode = ReadFile(filepath);

        ShaderID = glCreateShader(gltype);
        const char *csource = shadersourcecode.c_str();
        glShaderSource(ShaderID, 1, &csource, 0);
        glCompileShader(ShaderID);

        GLint iscompiled = GL_FALSE;
        glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &iscompiled);
        if (iscompiled == GL_FALSE)
        {
            GLint maxlength = 0;
            glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &maxlength);

            std::vector<GLchar> infolog(maxlength);
            glGetShaderInfoLog(ShaderID, maxlength, &maxlength, &infolog[0]);
            glDeleteShader(ShaderID);

            printf("Shader Compilation failed: \n%s", infolog.data());

            ShaderID = UINT32_MAX;
            return false;
        }
        return true;
    }
    void Shader::destroy()
    {
        if (ShaderID != UINT32_MAX)
        {
            glDeleteShader(ShaderID);
            ShaderID = UINT32_MAX;
        }
        if (filepath != nullptr)
        {
            free(filepath);
            filepath = nullptr;
        }
    }
    GLenum Shader::toglenumType(ShaderType type)
    {
        if (type == ShaderType::Vertex)
        {
            return GL_VERTEX_SHADER;
        }
        else if (type == ShaderType::Fragment)
        {
            return GL_FRAGMENT_SHADER;
        }
        return GL_INVALID_ENUM;
    }
    static std::string ReadFile(const char *filepath)
    {
        std::string result;
        std::ifstream in(filepath, std::ios::in | std::ios::binary);
        if (in)
        {
            in.seekg(0, std::ios::end);
            result.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&result[0], result.size());
            in.close();
        }
        else
        {
            printf("Could not open file: '%s'", filepath);
        }
        return result;
    }
}