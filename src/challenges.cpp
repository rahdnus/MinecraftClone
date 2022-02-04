#include "core/challenge.hpp"

using namespace Minecraft::Math;

namespace Minecraft::Ch1{

GLuint Vao_ID;
GLuint Vbo_ID;

Vertex vertex[3]={
    {glm::vec4(0,1,1,1),glm::vec3(0.5f,-0.5f,0)},
    {glm::vec4(1,0,1,1),glm::vec3(-0.5f,0.5f,0)},
    {glm::vec4(1,1,0,1),glm::vec3(-0.5f,-0.5f,0)}
};
void SetUp()
{
    glCreateVertexArrays(1,&Vao_ID);
    glBindVertexArray(Vao_ID);

    glCreateBuffers(1,&Vbo_ID);
    glBindBuffer(GL_ARRAY_BUFFER,Vbo_ID);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertex),vertex,GL_STATIC_DRAW);

    glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,color));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,position ));
    glEnableVertexAttribArray(1);
}
void Draw()
{
    glBindVertexArray(Vao_ID);
    glDrawArrays(GL_TRIANGLES,0,3);
}
void Delete()
{
    glDeleteBuffers(1,&Vbo_ID);
    glDeleteVertexArrays(1,&Vao_ID);
}
}
namespace Minecraft::Ch2{
    GLuint Vao_ID;
    GLuint Vbo_ID;
    GLuint Ebo_ID;

    GLuint indices[]={
     0,1,2,
     0,2,3
    };
    Vertex vertex[]={
    {glm::vec4(0,1,1,1),glm::vec3(-0.5f,-0.5f,0)},
    {glm::vec4(1,0,1,1),glm::vec3(-0.5f,0.5f,0)},
    {glm::vec4(1,1,0,1),glm::vec3(0.5f,0.5f,0)},
    {glm::vec4(1,1,0,1),glm::vec3(0.5f,-0.5f,0)}
};
    void SetUp()
    {
        printf("\nin setup2");
        glCreateVertexArrays(1,&Vao_ID);
        glBindVertexArray(Vao_ID);

        glCreateBuffers(1,&Vbo_ID);
        glBindBuffer(GL_ARRAY_BUFFER,Vbo_ID);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertex),vertex,GL_STATIC_DRAW);

        glCreateBuffers(1,&Ebo_ID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,Ebo_ID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
        
        glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,color));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,position));
        glEnableVertexAttribArray(1);
        
  
    }

    void Draw()
    {
        printf("\nin draw2");

        glBindVertexArray(Vao_ID);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    }
    void Delete()
    {
                printf("\nin delete2");

        glDeleteBuffers(1,&Ebo_ID);
        glDeleteBuffers(1,&Vbo_ID);
        glDeleteVertexArrays(1,&Vao_ID);
    }

}




