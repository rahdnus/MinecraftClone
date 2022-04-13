#include<Renderer/ShaderProgram.hpp>


namespace Core
{

struct ShaderVariable{
    GLint varlocation;
    std::string name;
    uint32_t ID;

    bool operator==(const ShaderVariable& other) const 
    {
        return other.ID==ID && other.name==name;
    }
};

static std::unordered_set<ShaderVariable> allShaderVariableLocations;

bool ShaderProgram::compile(const char* vertexPath,const char* fragmentPath)
{
    GLint programID=glCreateProgram();

    if(!vertexShader.compile(ShaderType::Vertex,vertexPath))
    {
        vertexShader.destroy();
        return false;
    }

    if(!fragmentShader.compile(ShaderType::Fragment,fragmentPath))
    {
        fragmentShader.destroy();
        return false;
    }


    glAttachShader(programID,vertexShader.ID);
    glAttachShader(programID,fragmentShader.ID);
    glLinkProgram(programID);


    GLint islinked=GL_FALSE;
    glGetProgramiv(programID,GL_LINK_STATUS,&islinked);
    if(islinked==GL_FALSE)
    {
        GLint length;
        glGetProgramiv(programID,GL_INFO_LOG_LENGTH,&length);

        std::vector<GLchar> info(length);
        glGetProgramInfoLog(programID,length,&length,&info[0]);

        // glDetachShader(ID,vertexShader.ID);
        // glDetachShader(ID,fragmentShader.ID);

        vertexShader.destroy();
        fragmentShader.destroy();

        printf("Shader Program Linking Failed:%s",info);
        programID=UINT32_MAX;
        return false;
    }

    glDetachShader(programID,vertexShader.ID);
    glDetachShader(programID,fragmentShader.ID);
    
    vertexShader.destroy();
    fragmentShader.destroy();


    int numofUniforms;
    glGetProgramiv(programID,GL_ACTIVE_UNIFORMS,&numofUniforms);

    int maxCharLength;
    glGetProgramiv(programID,GL_ACTIVE_UNIFORM_MAX_LENGTH,&maxCharLength);

    if(numofUniforms>0 && maxCharLength>0)
    {
        char* uniformBuffer=(char *)malloc(sizeof(char)*(maxCharLength+1));

        for(int i=0;i<numofUniforms;i++)
        {
            int length,size;
            GLenum type;
            glGetActiveUniform(programID,i,maxCharLength,&length,&size,&type,&uniformBuffer[0]);
            GLint location=glGetUniformLocation(programID,uniformBuffer);
            ShaderVariable shaderVar;

            shaderVar.name=std::string(uniformBuffer);
            shaderVar.varlocation=location;
            shaderVar.ID=programID;
            
            allShaderVariableLocations.emplace(shaderVar);//wtf it works in old-state branch
        }
        free(uniformBuffer);
    }
    ID=programID;
    printf("Shader compilation and Linking successful <Vertex:%s><Fragment:%s>",vertexPath,fragmentPath);
    return true;


}
}