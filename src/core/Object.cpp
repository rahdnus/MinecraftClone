#include<core/Object.hpp>
using namespace Engine;

void Mesh::Init()
{
    glCreateVertexArrays(1,&VAO_ID);
    glBindVertexArray(VAO_ID);
    
    glCreateBuffers(1,&VBO_ID);
    glBindBuffer(GL_ARRAY_BUFFER,VBO_ID);
    
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertex),vertex,GL_STATIC_DRAW);

    glCreateBuffers(1,&EBO_ID);    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,color));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
}
void Mesh::Bind()
{
    glBindVertexArray(VAO_ID);
}
void Mesh::Draw()
{
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    // GLint data;
    // glGetIntegerv( GL_VERTEX_ARRAY_BINDING,&data);
    // printf("%d",data);
}
