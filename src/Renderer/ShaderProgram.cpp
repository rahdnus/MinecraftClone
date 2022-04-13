#include<Renderer/ShaderProgram.hpp>

using namespace Core;

bool ShaderProgram::compile(const char* vertexPath,const char* fragmentPath)
{
    
    
    vertexShader.compile(ShaderType::Vertex,vertexPath);



    fragmentShader.compile(ShaderType::Fragment,fragmentPath);


}