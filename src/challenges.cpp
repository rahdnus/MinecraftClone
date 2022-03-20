#include "challenge.hpp"
#define STB_IMAGE_IMPLEMENTATION    
#include "stb_image.h"

using namespace Minecraft::Math;

namespace Minecraft::Ch1{

GLuint Vao_ID;
GLuint Vbo_ID;
GLuint Tex_ID;
Vertex vertex[3]={
    {glm::vec4(0,1,1,1),glm::vec3(0.5f,-0.5f,0),glm::vec2(0.0,1.0)},
    {glm::vec4(1,0,1,1),glm::vec3(-0.5f,0.5f,0),glm::vec2(1.0,0.0)},
    {glm::vec4(1,1,0,1),glm::vec3(-0.5f,-0.5f,0),glm::vec2(0.0,0.0)}
};

void SetUp()
{
 
      
    int width,height,nrchannels;
    stbi_set_flip_vertically_on_load(true);  
    unsigned char *data=stbi_load("assets/aqua1.png",&width,&height,&nrchannels,0); 
    glCreateTextures(GL_TEXTURE_2D,1,&Tex_ID);
    glBindTexture(GL_TEXTURE_2D,Tex_ID);


 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,0);

    glCreateVertexArrays(1,&Vao_ID);
    glBindVertexArray(Vao_ID);


    glCreateBuffers(1,&Vbo_ID);
    glBindBuffer(GL_ARRAY_BUFFER,Vbo_ID);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertex),vertex,GL_STATIC_DRAW);

    glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,color));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,position));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,texcoords));
    glEnableVertexAttribArray(2);
     glBindVertexArray(0);
}
void Draw()
{
    glDrawArrays(GL_TRIANGLES,0,3);
}
void Bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,Tex_ID);
    glBindVertexArray(Vao_ID);
}
void Delete()
{
    // glDeleteBuffers(1,&Vbo_ID);
    // glDeleteVertexArrays(1,&Vao_ID);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindVertexArray(0);
}
}
namespace Minecraft::Ch2{
    GLuint Vao_ID;
    GLuint Vbo_ID;
    GLuint Ebo_ID;
    GLuint Tex_ID1;
    GLuint Tex_ID2;

    GLuint indices[]={
     0,1,3,
     1,2,3
    };
//     Vertex vertex[]={
//     {glm::vec4(1,1,0,1),glm::vec3(0.5f,0.5f,0),glm::vec2(1,1)},
//     {glm::vec4(1,1,0,1),glm::vec3(0.5f,-0.5f,0),glm::vec2(1,0)},
//     {glm::vec4(0,1,1,1),glm::vec3(-0.5f,-0.5f,0),glm::vec2(0,0)},
//     {glm::vec4(1,0,1,1),glm::vec3(-0.5f,0.5f,0),glm::vec2(0,1)}
// };
    Vertex vertex[] = {{glm::vec4(1, 1, 0, 1), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f),glm::vec3(0.0f,  0.0f, -1.0f)},
                       {glm::vec4(1, 0, 1, 1), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f),glm::vec3(  0.0f,  0.0f, -1.0f)},
                       {glm::vec4(0, 1, 1, 1), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 1.0f),glm::vec3(0.0f,  0.0f, -1.0f)},
                       {glm::vec4(1, 1, 0, 1), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 1.0f),glm::vec3(0.0f,  0.0f, -1.0f)},
                       {glm::vec4(1, 0, 1, 1), glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 1.0f),glm::vec3(0.0f,  0.0f, -1.0f)},
                       {glm::vec4(0, 1, 1, 1), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f),glm::vec3(0.0f,  0.0f, -1.0f)},

                       {glm::vec4(1, 1, 0, 1), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f),glm::vec3(0.0f,  0.0f, 1.0f)},
                       {glm::vec4(1, 0, 1, 1), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1.0f, 0.0f),glm::vec3(0.0f,  0.0f, 1.0f)},
                       {glm::vec4(0, 1, 1, 1), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 1.0f),glm::vec3(0.0f,  0.0f, 1.0f)},
                       {glm::vec4(1, 1, 0, 1), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 1.0f),glm::vec3(0.0f,  0.0f, 1.0f)},
                       {glm::vec4(1, 0, 1, 1), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 1.0f),glm::vec3(0.0f,  0.0f, 1.0f)},
                       {glm::vec4(0, 1, 1, 1), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f),glm::vec3(0.0f,  0.0f, 1.0f)},

                       {glm::vec4(1, 1, 0, 1), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 0.0f),glm::vec3(1.0f,  0.0f,  0.0f)},
                       {glm::vec4(1, 0, 1, 1), glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 1.0f),glm::vec3(1.0f,  0.0f,  0.0f)},
                       {glm::vec4(0, 1, 1, 1), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f),glm::vec3(1.0f,  0.0f,  0.0f)},
                       {glm::vec4(1, 1, 0, 1), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f),glm::vec3(1.0f,  0.0f,  0.0f)},
                       {glm::vec4(1, 0, 1, 1), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f),glm::vec3(1.0f,  0.0f,  0.0f)},
                       {glm::vec4(0, 1, 1, 1), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 0.0f),glm::vec3(1.0f,  0.0f,  0.0f)},

                       {glm::vec4(1, 1, 0, 1), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 0.0f),glm::vec3(1.0f,  0.0f,  0.0f)},
                       {glm::vec4(1, 0, 1, 1), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 1.0f),glm::vec3(1.0f,  0.0f,  0.0f)},
                       {glm::vec4(0, 1, 1, 1), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f),glm::vec3(1.0f,  0.0f,  0.0f)},
                       {glm::vec4(1, 1, 0, 1), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f),glm::vec3(1.0f,  0.0f,  0.0f)},
                       {glm::vec4(1, 0, 1, 1), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f),glm::vec3(1.0f,  0.0f,  0.0f)},
                       {glm::vec4(0, 1, 1, 1), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 0.0f),glm::vec3(1.0f,  0.0f,  0.0f)},

                       {glm::vec4(1, 1, 0, 1), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f),glm::vec3(0.0f, -1.0f,  0.0f)},
                       {glm::vec4(1, 0, 1, 1), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 1.0f),glm::vec3(0.0f, -1.0f,  0.0f)},
                       {glm::vec4(0, 1, 1, 1), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1.0f, 0.0f),glm::vec3(0.0f, -1.0f,  0.0f)},
                       {glm::vec4(1, 1, 0, 1), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1.0f, 0.0f),glm::vec3(0.0f, -1.0f,  0.0f)},
                       {glm::vec4(1, 0, 1, 1), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f),glm::vec3(0.0f, -1.0f,  0.0f)},
                       {glm::vec4(0, 1, 1, 1), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f),glm::vec3(0.0f, -1.0f,  0.0f)},

                       {glm::vec4(1, 1, 0, 1), glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 1.0f),glm::vec3(0.0f,  1.0f,  0.0f)},
                       {glm::vec4(1, 0, 1, 1), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 1.0f),glm::vec3(0.0f,  1.0f,  0.0f)},
                       {glm::vec4(0, 1, 1, 1), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 0.0f),glm::vec3(0.0f,  1.0f,  0.0f)},
                       {glm::vec4(1, 1, 0, 1), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 0.0f),glm::vec3(0.0f,  1.0f,  0.0f)},
                       {glm::vec4(1, 0, 1, 1), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 0.0f),glm::vec3(0.0f,  1.0f,  0.0f)},
                       {glm::vec4(0, 1, 1, 1), glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 1.0f),glm::vec3(0.0f,  1.0f,  0.0f)}};
  
 
    void SetUp()
    {
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        stbi_set_flip_vertically_on_load(true);  

        int width,height,nrchannels;
        unsigned char *data=stbi_load("assets/hachi.jpg",&width,&height,&nrchannels,4);
    
        glGenTextures(1, &Tex_ID1);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,Tex_ID1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,0);
        stbi_image_free(data);

        data=stbi_load("assets/money.jpg",&width,&height,&nrchannels,4);
    
        glGenTextures(1, &Tex_ID2);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,Tex_ID2);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,0);

        glBindTexture(GL_TEXTURE_2D,0);

        glCreateVertexArrays(1,&Vao_ID);
        glBindVertexArray(Vao_ID);

        glCreateBuffers(1,&Vbo_ID);
        glBindBuffer(GL_ARRAY_BUFFER,Vbo_ID);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertex),vertex,GL_STATIC_DRAW);

        // glCreateBuffers(1,&Ebo_ID);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,Ebo_ID);
        // glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
        
        glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,color));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,position));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,texcoords));
        glEnableVertexAttribArray(2);  
        
        glVertexAttribPointer(3,3,GL_FLOAT,GL_FALSE,sizeof(Math::Vertex),(void*)offsetof(Vertex,normal));
        glEnableVertexAttribArray(3);      
        
        glBindVertexArray(0);

    }
    void Bind()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,Tex_ID1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,Tex_ID2);
        glBindVertexArray(Vao_ID);
    }
    void Draw()
    {

           glDrawArrays(GL_TRIANGLES,0,36);
    }
    void Delete()
    {

        // glDeleteBuffers(1,&Ebo_ID);
        // glDeleteBuffers(1,&Vbo_ID);
        // glDeleteVertexArrays(1,&Vao_ID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindVertexArray(0);

    }

}
namespace Minecraft::Ch3{
    GLuint Vao_ID;
    GLuint Vbo_ID;
    GLuint Ebo_ID;
    GLuint Tex_ID;

    GLuint indices[]={
     0,1,9,     6,5,7,      1,3,7,
     1,2,3,     7,8,9,      3,5,7,
     3,4,5,     1,9,7

    };
    Vertex vertex[]={
    {glm::vec4(0,1,1,1),glm::vec3(0,0.75f,0)},
    {glm::vec4(0,1,1,1),glm::vec3(-0.2f,0.2f,0)},
    {glm::vec4(1,1,0,1),glm::vec3(-0.55f,0.1f,0)},
    {glm::vec4(1,1,0,1),glm::vec3(-0.3f,-0.2f,0)},
    {glm::vec4(1,0,1,1),glm::vec3(-0.40f,-0.75f,0)},
    {glm::vec4(1,0,1,1),glm::vec3(0,-0.4f,0)},
    {glm::vec4(1,0,1,1),glm::vec3(0.40f,-0.75f,0)},
    {glm::vec4(1,1,0,1),glm::vec3(0.3f,-0.2f,0)},
    {glm::vec4(1,1,0,1),glm::vec3(0.55f,0.1f,0)},
    {glm::vec4(0,1,1,1),glm::vec3(0.2f,0.2f,0)},
};
    void SetUp()
    {
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
        
        glBindVertexArray(0);

  
    }
    void Bind()
    {
        glBindVertexArray(Vao_ID);
    }
    void Draw()
    {

        glDrawElements(GL_TRIANGLES,24,GL_UNSIGNED_INT,0);
    }
    void Delete()
    {

        // glDeleteBuffers(1,&Ebo_ID);
        // glDeleteBuffers(1,&Vbo_ID);
        // glDeleteVertexArrays(1,&Vao_ID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindVertexArray(0);
    }

}
namespace Minecraft::Ch4{
    GLuint Vao_ID;
    GLuint Vbo_ID;
    GLuint Ebo_ID;
    GLuint Tex_ID;

    GLuint indices[]={
    0,1,1,2,2,3,3,0
    };
    Vertex vertex[]={
    {glm::vec4(0,1,1,1),glm::vec3(0.5,0.5f,0)},
    {glm::vec4(0,1,1,1),glm::vec3(-0.5f,0.5f,0)},
    {glm::vec4(1,1,0,1),glm::vec3(-0.5f,-0.5f,0)},
    {glm::vec4(1,1,0,1),glm::vec3(0.5f,-0.5f,0)},
};
    void SetUp()
    {
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
        
        glBindVertexArray(0);
    }
    void Bind()
    {
        glBindVertexArray(Vao_ID);

    }
    void Draw()
    {
        glDrawElements(GL_LINES,8,GL_UNSIGNED_INT,0);
    }
    void Delete()
    {

        // glDeleteBuffers(1,&Ebo_ID);
        // glDeleteBuffers(1,&Vbo_ID);
        // glDeleteVertexArrays(1,&Vao_ID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindVertexArray(0);
    }   

}







