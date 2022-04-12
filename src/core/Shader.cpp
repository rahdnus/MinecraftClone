#include<Renderer/Shader.hpp>

using namespace Core::Shaders;

static const char* readPath(const char* path);

bool Shader::compile(ShaderType type,const char* path)
{
    GLenum typeofShader=toGLenumType(type);

    ID=glCreateShader(typeofShader);

    int sourcelength=std::strlen(path);
    filepath=(char *)malloc(sizeof(char)*(sourcelength+1));

    std::strcpy(filepath,path);
    filepath[sourcelength]='\0';

    const char *source=readPath(filepath);
    /* TODORead data from path and give it to glshadersource*/

    glShaderSource(ID,1,&source,0);
    glCompileShader(ID);

    return false;

}
GLenum Shader::toGLenumType(ShaderType type)
{
    switch (type)
    {
    case ShaderType::Vertex:
        return GL_VERTEX_SHADER;
    case ShaderType::Fragment:
        return GL_FRAGMENT_SHADER;
    default:
        return GL_INVALID_ENUM;
    }
}

static const char* readPath(const char* path)
{
    std::string source;
    std::ifstream in(path,std::ios::in|std::ios::binary);

    if(in)
    {
        in.seekg(0,std::ios::end);
        source.resize(in.tellg());
        in.seekg(0,std::ios::beg);
        in.read(&source[0],source.length());
        in.close();
    }
    else
    {
        printf("Could not open file path:%s",path);
    }
    return source.c_str();
}