#include<Renderer/ShaderProgram.hpp>

using namespace Core;

bool ShaderProgram::compile(const char* vertexPath,const char* fragmentPath)
{
    
    
   bool vresult= vertexShader.compile(ShaderType::Vertex,vertexPath);
    if(!vresult)
    {
        vertexShader.destroy();
        return false;
    }

    bool fresult=fragmentShader.compile(ShaderType::Fragment,fragmentPath);
    if(!fresult)
    {
        fragmentShader.destroy();
        return false;
    }

    ID=glCreateProgram();

    glAttachShader(ID,vertexShader.ID);
    glAttachShader(ID,fragmentShader.ID);
    glLinkProgram(ID);


    GLint islinked=GL_FALSE;
    glGetProgramiv(ID,GL_LINK_STATUS,&islinked);
    if(islinked==GL_FALSE)
    {
        GLint length;
        glGetProgramiv(ID,GL_INFO_LOG_LENGTH,&length);

        std::vector<GLchar> info(length);
        glGetProgramInfoLog(ID,length,&length,&info[0]);

        // glDetachShader(ID,vertexShader.ID);
        // glDetachShader(ID,fragmentShader.ID);

        vertexShader.destroy();
        fragmentShader.destroy();

        printf("Shader Program Linking Failed:%s",info);
        ID=UINT32_MAX;
        return false;
    }

    glDetachShader(ID,vertexShader.ID);
    glDetachShader(ID,fragmentShader.ID);
    
    vertexShader.destroy();
    fragmentShader.destroy();


    int numofUniforms;
    glGetProgramiv(ID,GL_ACTIVE_UNIFORMS,&numofUniforms);

    int maxCharLength;
    glGetProgramiv(ID,GL_ACTIVE_UNIFORM_MAX_LENGTH,&maxCharLength);

    if(numofUniforms>0 && maxCharLength>0)
    {
        char* uniformBuffer=(char *)malloc(sizeof(char)*(maxCharLength+1));

        for(int i=0;i<numofUniforms;i++)
        {
            
        }
    }



}