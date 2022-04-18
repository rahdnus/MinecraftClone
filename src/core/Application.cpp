
#include<core/Application.hpp>
#include<Renderer/ShaderProgram.hpp>

using namespace Core;

    GLuint VAO_ID,VBO_ID;

Vertex vertex[3]={
    {glm::vec4(0,1,1,1),glm::vec3(0.5f,-0.5f,0)},
    {glm::vec4(1,0,1,1),glm::vec3(-0.5f,0.5f,0)},
    {glm::vec4(1,0,1,1),glm::vec3(-0.5f,-0.5f,0)}
};
ShaderProgram program;
int Application::windowInit(GLuint width,GLuint height,std::string name)
{

    mywindow=glfwCreateWindow(width,height,name.c_str(),NULL,NULL);
    if(!mywindow)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(mywindow);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    
    program.compile("Shaders/SimpleVert.glsl","Shaders/SimpleFrag.glsl");

    glCreateVertexArrays(1,&VAO_ID);
    glBindVertexArray(VAO_ID);
    
    glCreateBuffers(1,&VBO_ID);
    glBindBuffer(GL_ARRAY_BUFFER,VBO_ID);
    
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertex),vertex,GL_STATIC_DRAW);
    
  
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,position));
    glEnableVertexAttribArray(0);
      glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,color));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);



}
int Application::run()
{

    while(!glfwWindowShouldClose(mywindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);
    program.bind();
    glBindVertexArray(VAO_ID);
        glDrawArrays(GL_TRIANGLES,0,3);
        glfwSwapBuffers(mywindow);
        glfwPollEvents();
    }
}
