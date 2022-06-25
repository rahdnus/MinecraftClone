#include<Renderer/Shader.hpp>
#include<stdio.h>
using namespace Engine;

std::string readPath(const char* path);

bool Shader::compile(ShaderType type,const char* path)
{
    GLenum typeofShader=toGLenumType(type);

    ID=glCreateShader(typeofShader);

    int sourcelength=std::strlen(path);
    filepath=(char *)malloc(sizeof(char)*(sourcelength+1));

    std::strcpy(filepath,path);
    filepath[sourcelength]='\0';

   std::string source=readPath(filepath);
//    printf("%s",source);
   const GLchar* sourcecode=source.c_str();

    glShaderSource(ID,1,&sourcecode,0);
    glCompileShader(ID);

    GLint iscompiled=GL_FALSE;
    glGetShaderiv(ID,GL_COMPILE_STATUS,&iscompiled);

    if(iscompiled==GL_FALSE)
    {
          /*TODO 
        ✅log potential errors*/
        GLint maxlength;
        glGetShaderiv(ID,GL_INFO_LOG_LENGTH,&maxlength);

        std::vector<GLchar> info(maxlength);
        glGetShaderInfoLog(ID,maxlength,&maxlength,&info[0]);
        glDeleteShader(ID);
        ID=UINT32_MAX;

        printf("Shader Compilation Failed:%s",info.data());
        return false;

    }
  
    return true;

}
void Shader::destroy()
{
    if(ID!=UINT32_MAX)
    {
        glDeleteShader(ID);
        ID=UINT32_MAX;
    }
    if(filepath!=nullptr)
    {
        free(filepath);
        filepath=nullptr;
    }
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

std::string readPath(const char* path)
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
    // source.resize(source.length()+1);
    // source[source.length()]='\0';
    return source;

}